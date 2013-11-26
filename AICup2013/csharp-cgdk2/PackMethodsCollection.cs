using System;
using System.Collections.Generic;
using Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk.Model;

namespace Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk
{
    partial class Pack
    {

        void update(Trooper self, World world, Game game)
        {
            this.world = world;
            this.game = game;
            updateTroopers();
            updateCells();

            miniTurnNumber++;
            if (miniTurnNumber == 1) firstUpdate(pos(self));

            updateCheckPoints(pos(self));
        }

        void firstUpdate(Point fstPoint)
        {
            write("First update");
            visualtyUpdate();
            checkPointsUpdate(fstPoint);
        }

        void checkPointsUpdate(Point p)
        {
            write("Update check points");
            int w = world.Width;
            int h = world.Height;
            int x = p.x;
            int y = p.y;
            checkPoints = new Queue<Point>();

            checkPoints.Enqueue(findClosestFree(x * 2 < w ? w / 3 : 2 * w / 3, h / 2));
            checkPoints.Enqueue(findClosestFree(x, h - y));

            checkPoints.Enqueue(findClosestFree(w / 2, y * 2 > h ? h / 4 : 3 * h / 4));
            checkPoints.Enqueue(findClosestFree(w - x, h - y));

            checkPoints.Enqueue(findClosestFree(x * 2 > w ? w / 3 : 2 * w / 3, h / 2));
            checkPoints.Enqueue(findClosestFree(w - x, y));

            checkPoints.Enqueue(findClosestFree(w / 2, y * 2 < h ? h / 4 : 3 * h / 4));
            checkPoints.Enqueue(findClosestFree(x, y));
        }

        Point findClosestFree(int x, int y)
        {
            int w = world.Width;
            int h = world.Height;
            for (int dy = 0; dy < h; dy++)
            {
                for (int dx = 0; dx < 2; dx++)
                {
                    if (!isWall(x + dx, y + dy))
                    {
                        return new Point(x + dx, y + dy);
                    }
                    if (!isWall(x + dx, y - dy))
                    {
                        return new Point(x + dx, y - dy);
                    }
                    if (!isWall(x - dx, y + dy))
                    {
                        return new Point(x - dx, y + dy);
                    }
                    if (!isWall(x - dx, y - dy))
                    {
                        return new Point(x - dx, y - dy);
                    }
                }
            }
            return new Point(0, 0);
        }

        void visualtyUpdate()
        {
            int w = world.Width;
            int h = world.Height;
            visualty = new int[w][];
            for (int i = 0; i < w; i++)
            {
                visualty[i] = new int[h];
                for (int j = 0; j < h; j++)
                {
                    visualty[i][j] = 0;
                    if (!isWall(i, j))
                    {
                        for (int x = 0; x < w; x++)
                        {
                            for (int y = 0; y < h; y++)
                            {
                                if (!isWall(x, y))
                                {
                                    for (int st = 0; st < 3; st++)
                                    {
                                        if (world.IsVisible(averageVisualRange, i, j, stance(st), x, y, TrooperStance.Standing))
                                        {
                                            visualty[i][j] += 3 - st;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            for (int y = 0; y < h; y++)
            {
                string s = "";
                for (int x = 0; x < w; x++)
                {
                    s += "\t" + visualty[x][y];
                }
                write(s);
            }
        }

        bool isWall(int x, int y)
        {
            return !isInsideWorld(x, y) || world.Cells[x][y] != CellType.Free;
        }

        bool isWall(Point p)
        {
            return isWall(p.x, p.y);
        }
        
        void updateCheckPoints(Point p)
        {
            Point cp = nextCheckPoint();
            if (p.distanceTo(cp) <= checkPointMarkDist)
            {
                checkPoints.Dequeue();
            }
        }

        Point nextCheckPoint()
        {
            return checkPoints.Count == 0 ? new Point(0, 0) : checkPoints.Peek().copy();
        }

        void updateTroopers()
        {
            visibleEnemies = new List<Trooper>();
            teammates = new List<Trooper>();

            int newHurtCount = 0;

            for (int i = 0; i < world.Troopers.Length; i++)
            {
                if (world.Troopers[i].IsTeammate)
                {
                    teammates.Add(world.Troopers[i]);
                    if (!amIHealthy(world.Troopers[i]))
                    {
                        newHurtCount++;
                    }
                    if (lastTrooper == world.Troopers[i].Type)
                    {
                        bonusesCountChanged = bonusesCount != bonusesAmount(world.Troopers[i]);
                        bonusesCount = bonusesAmount(world.Troopers[i]);
                    }
                }
                else
                {
                    visibleEnemies.Add(world.Troopers[i]);
                }
            }

            teamSizeChanged = teammates.Count != teamSize;
            teamSize = teammates.Count;

            enemiesCountChanged = visibleEnemies.Count != enemiesCount;
            enemiesCount = visibleEnemies.Count;

            teamHurtCountChanged = newHurtCount != teamHurtCount;
            teamHurtCount = newHurtCount;

            TrooperHurtComparer hc = new TrooperHurtComparer();
            teammates.Sort(hc);
            visibleEnemies.Sort(hc);

            if (enemiesCount == 0) turnsWithoutBattle++;
            if (enemiesCount > 0) turnsWithoutBattle = 0;
        }

        void updateCells()
        {
            isFreePoint = new bool[world.Width][];
            for (int i = 0; i < world.Width; i++)
            {
                isFreePoint[i] = new bool[world.Height];

                for (int j = 0; j < world.Height; j++)
                {
                    isFreePoint[i][j] = !isWallThere(new Point(i, j));
                }
            }
            foreach (Trooper tr in teammates)
            {
                isFreePoint[tr.X][tr.Y] = false;
            }
            foreach (Trooper tr in visibleEnemies)
            {
                isFreePoint[tr.X][tr.Y] = false;
            }
        }

        public bool isItNewTurn(Trooper self)
        {
            return (self.ActionPoints == self.InitialActionPoints +
                    (isCommanderNear(self) ? game.CommanderAuraBonusActionPoints : 0));
        }

        public bool isInsideWorld(Point p)
        {
            return isInsideWorld(p.x, p.y);
        }

        public bool isInsideWorld(int x, int y)
        {
            return (x >= 0 && x < world.Width) && (y >= 0 && y < world.Height);
        }

        public int moveCost(TrooperStance st)
        {
            switch (st)
            {
                case TrooperStance.Prone:
                    return (game.ProneMoveCost);
                case TrooperStance.Kneeling:
                    return (game.KneelingMoveCost);
                case TrooperStance.Standing:
                    return (game.StandingMoveCost);
            }
            return game.ProneMoveCost;
        }

        public bool isFree(Point p)
        {
            return isInsideWorld(p) && isFreePoint[p.x][p.y];
        }

        public int standingUpCost(TrooperStance stance)
        {
            return changeStanceCost(stance, TrooperStance.Standing);
        }

        public bool canMove(Trooper self)
        {
            return self.ActionPoints >= moveCost(self.Stance);
        }

        public bool isWallThere(Point p)
        {
            return (!isInsideWorld(p) || (world.Cells[p.x][p.y] != CellType.Free));
        }

        public bool amICommander(Trooper self)
        {
            return self.Type == TrooperType.Commander;
        }

        public bool amIFieldMedic(Trooper self)
        {
            return self.Type == TrooperType.FieldMedic;
        }

        public bool amISoldier(Trooper self)
        {
            return self.Type == TrooperType.Soldier;
        }

        public Direction getRandomDirection()
        {
            if (random.Next(2) == 0)
            {
                return random.Next(2) == 0 ? Direction.North : Direction.South;
            }
            else
            {
                return random.Next(2) == 0 ? Direction.West : Direction.East;
            }
        }

        public Point dtp(Direction direction)
        {
            switch (direction)
            {
                case Direction.North:
                    return new Point(0, -1);
                case Direction.South:
                    return new Point(0, 1);
                case Direction.West:
                    return new Point(-1, 0);
                case Direction.East:
                    return new Point(1, 0);
                case Direction.CurrentPoint:
                    return new Point(0, 0);
            }
            return new Point(0, 0);
        }

        public Point pos(Unit unit)
        {
            return new Point(unit.X, unit.Y);
        }

        public List<Direction> dirsList()
        {
            List<Direction> dirs = new List<Direction>();
            dirs.Add(Direction.North);
            dirs.Add(Direction.South);
            dirs.Add(Direction.West);
            dirs.Add(Direction.East);
            return dirs;
        }

        public List<Direction> dirsListRandOrder()
        {
            List<Direction> dirs = new List<Direction>();
            while (dirs.Count < 4)
            {
                Direction d = getRandomDirection();
                if (!dirs.Contains(d))
                {
                    dirs.Add(d);
                }
            }
            return dirs;
        }

        Point randomPoint()
        {
            Point p = new Point(random.Next(world.Width), random.Next(world.Height));
            while (!isFree(p))
            {
                p = new Point(random.Next(world.Width), random.Next(world.Height));
            }
            return p;
        }

        public Direction opposite(Direction direction)
        {
            switch (direction)
            {
                case Direction.North:
                    return Direction.South;
                case Direction.South:
                    return Direction.North;
                case Direction.West:
                    return Direction.East;
                case Direction.East:
                    return Direction.West;
                default:
                    return Direction.CurrentPoint;
            }
        }

        public bool isTeammateThere(Trooper man, Point p)
        {
            if (!isInsideWorld(p)) return false;
            foreach (Trooper tr in world.Troopers)
            {
                if (tr.X == p.x && tr.Y == p.y && man.PlayerId == tr.PlayerId)
                {
                    return true;
                }
            }
            return false;
        }

        public bool isEnemyThere(Trooper man, Point p)
        {
            if (!isInsideWorld(p)) return false;
            foreach (Trooper tr in world.Troopers)
            {
                if (tr.X == p.x && tr.Y == p.y && man.PlayerId != tr.PlayerId)
                {
                    return true;
                }
            }
            return false;
        }
        
        public bool isCommanderNear(Trooper self)
        {
            if (amICommander(self)) return false;
            foreach (Trooper tr in teammates)
            {
                if (amICommander(tr) && self.GetDistanceTo(tr) <= game.CommanderAuraRange)
                {
                    return true;
                }
            }
            return false;
        }

        public bool amIHealthy(Trooper self)
        {
            return self.Hitpoints >= 100;
        }

        public bool canHeal(Trooper self)
        {
            return amIFieldMedic(self) && (self.ActionPoints >= game.FieldMedicHealCost);
        }

        int stanceId(TrooperStance stance)
        {
            switch (stance)
            {
                case TrooperStance.Prone: return 0;
                case TrooperStance.Kneeling: return 1;
                case TrooperStance.Standing: return 2;
            }
            return 2;
        }

        TrooperStance stance(int stanceId)
        {
            switch (stanceId)
            {
                case 0: return TrooperStance.Prone;
                case 1: return TrooperStance.Kneeling;
                case 2: return TrooperStance.Standing;
                default: return TrooperStance.Standing;
            }
        }

        int changeStanceCost(TrooperStance stSt, TrooperStance fnSt)
        {
            return game.StanceChangeCost * (Math.Abs(stanceId(stSt) - stanceId(fnSt)));
        }

        int grenadeDamage(Trooper man, Point target)
        {
            int damage = 0;
            foreach (Trooper enemy in world.Troopers)
            {
                if (enemy.PlayerId == man.PlayerId) continue;
                if (target.equal(pos(enemy)))
                {
                    damage += realDamage(enemy.Hitpoints, game.GrenadeDirectDamage);
                }
                else if (target.isAdjacentOrEqual(pos(enemy)))
                {
                    damage += realDamage(enemy.Hitpoints, game.GrenadeCollateralDamage);
                }
            }
            return damage;
        }

        int realDamage(int hp, int damage)
        {
            return damage > hp ? hp + game.TrooperEliminationScore : damage;
        }

        Trooper nearbyHurtest(Trooper self, Point selfPos)
        {
            foreach (Trooper tr in teammates)
            {
                if (selfPos.isAdjacentOrEqual(pos(tr)) && !amIHealthy(tr))
                {
                    return tr;
                }
            }
            return null;
        }

        bool withoutCoord(Move move)
        {
            return move.X > 100;
        }

        bool shouldRecalcStrategy(Trooper self)
        {
            return isItNewTurn(self) || isSmthChanged(self) || (strategy == null);
        }

        bool isSmthChanged(Trooper self)
        {
            return (self.Type != lastTrooper) || teamSizeChanged || enemiesCountChanged || teamHurtCountChanged || bonusesCountChanged;
        }

        List<Point> reachable(WayInfo[][] point)
        {
            int width = world.Width;
            int height = world.Height;
            List<Point> reached = new List<Point>();
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    if (point[i][j].reached())
                    {
                        reached.Add(new Point(i, j));
                    }
                }
            }
            return reached;
        }

        double bonusRelevance(Trooper self, Bonus bonus)
        {
            double k = 1.0;
            switch (bonus.Type)
            {
                case BonusType.FieldRation:
                    return (self.IsHoldingFieldRation) ? 0 : 1;
                case BonusType.Medikit: 
                    if (self.IsHoldingMedikit) return 0;
                    if (self.Hitpoints < valueCriticalHitpointsSelf)
                    {
                        k = 100.0 / self.Hitpoints;
                    }
                    break;
                case BonusType.Grenade:
                    if (self.IsHoldingGrenade) return 0;
                    int underGrenade = 1;
                    foreach (Trooper enemy in visibleEnemies)
                    {
                        if (enemy.GetDistanceTo(bonus) <= game.GrenadeThrowRange) underGrenade++;
                    }
                    return k * underGrenade;
            }
            return k;
        }
        
        int apAfterRelocation(int ap, TrooperStance stSt, TrooperStance fnSt, int length)
        {
            int maxR = -INFi;
            for (int st = 0; st < 3; st++)
            {
                TrooperStance tmpStance = stance(st);
                int tR = ap - changeStanceCost(stSt, tmpStance)
                            - length * moveCost(tmpStance)
                            - changeStanceCost(tmpStance, fnSt);
                if (tR > maxR) maxR = tR;
            }
            return maxR;
        }

        TrooperStance bestTempStance(int ap, TrooperStance stSt, TrooperStance fnSt, int length)
        {
            TrooperStance bestStance = TrooperStance.Standing;
            int maxR = -INFi;
            for (int st = 0; st < 3; st++)
            {
                TrooperStance tmpStance = stance(st);
                int tR = ap - changeStanceCost(stSt, tmpStance)
                            - length * moveCost(tmpStance)
                            - changeStanceCost(tmpStance, fnSt);
                if (tR > maxR)
                {
                    maxR = tR;
                    bestStance = tmpStance;
                }
            }
            return bestStance;
        }

        bool fieldMedicShouldHeal(Trooper self)
        {
            return amIFieldMedic(self) && !amIHealthy(teammates[0]);
        }

        void assignMove(Move to, Move from)
        {
            to.Action = from.Action;
            if (withoutCoord(from))
            {
                to.Direction = from.Direction;
            }
            else
            {
                to.X = from.X;
                to.Y = from.Y;
            }
        }

        public int actionCost(ActionType action, Trooper self)
        {
            switch (action)
            {
                case ActionType.EatFieldRation: return game.FieldRationEatCost;
                case ActionType.Heal: return game.FieldMedicHealCost;
                case ActionType.RaiseStance:
                case ActionType.LowerStance: return game.StanceChangeCost;
                case ActionType.Move: return moveCost(self.Stance);
                case ActionType.RequestEnemyDisposition: return game.CommanderRequestEnemyDispositionCost;
                case ActionType.Shoot: return self.ShootCost;
                case ActionType.ThrowGrenade: return game.GrenadeThrowCost;
                case ActionType.UseMedikit: return game.MedikitUseCost;
            }
            return moveCost(self.Stance);
        }

        public bool canDoThisMove(Trooper self, ActionType action)
        {
            return self.ActionPoints >= actionCost(action, self);
        }

        WayInfo[][] allWays(Point o, int maxLen)
        {
            int width = world.Width;
            int height = world.Height;
            Queue<Point> queue = new Queue<Point>();
            WayInfo[][] ways = new WayInfo[width][];

            for (int i = 0; i < width; i++)
            {
                ways[i] = new WayInfo[height];
                for (int j = 0; j < height; j++)
                {
                    ways[i][j] = new WayInfo();
                }
            }
            queue.Enqueue(o);
            ways[o.x][o.y].length = 0;
            PointComparer pc = new PointComparer();
            while (queue.Count > 0)
            {
                Point curr = queue.Dequeue();
                if (ways[curr.x][curr.y].length >= maxLen) continue;
                List<Direction> dirs = dirsListRandOrder();
                foreach (Direction dir in dirs)
                {
                    Point to = curr.add(dtp(dir));
                    if (!isWall(to))
                    {
                        if (!ways[to.x][to.y].reached()) queue.Enqueue(to);
                        int nlen = ways[curr.x][curr.y].length + 1;
                        if (nlen < ways[to.x][to.y].length ||
                            (nlen == ways[to.x][to.y].length && visualty[curr.x][curr.y] > ways[to.x][to.y].visualtyFrom))
                        {
                            ways[to.x][to.y].length = nlen;
                            ways[to.x][to.y].fromDirection = dir;
                            ways[to.x][to.y].visualtyFrom = visualty[curr.x][curr.y];
                        }
                    }
                }
            }
            return ways;
        }

        void concatQueues(Queue<Move> qto, Queue<Move> qfrom)
        {
            if (qto == null) qto = new Queue<Move>();
            if (qfrom == null) return;
            while (qfrom.Count > 0) qto.Enqueue(qfrom.Dequeue());
        }

        Queue<Move> changingStanceMoves(TrooperStance stSt, TrooperStance fnSt)
        {
            Queue<Move> changing = new Queue<Move>();
            int count = stanceId(fnSt) - stanceId(stSt);
            if (count >= 0)
            {
                for (int i = 0; i < count; i++)
                {
                    Move move = new Move();
                    move.Action = ActionType.RaiseStance;
                    move.X = 0;
                    changing.Enqueue(move);
                }
            }
            else
            {
                count = Math.Abs(count);
                for (int i = 0; i < count; i++)
                {
                    Move move = new Move();
                    move.Action = ActionType.LowerStance;
                    move.X = 0;
                    changing.Enqueue(move);
                }
            }
            return changing;
        }

        Stack<Move> createPath(Point start, Point end, WayInfo[][] ways)
        {
            Stack<Move> moves = new Stack<Move>();
            while (!end.equal(start))
            {
                Direction fromDir = ways[end.x][end.y].fromDirection;
                if (fromDir == Direction.CurrentPoint) break;
                Move move = new Move();
                move.Action = ActionType.Move;
                move.X = end.x;
                move.Y = end.y;
                moves.Push(move);
                end = end.add(dtp(opposite(fromDir)));
            }
            return moves;
        }

        PointInfo[][] initInfo()
        {
            int width = world.Width;
            int height = world.Height;
            PointInfo[][] info = new PointInfo[width][];
            for (int i = 0; i < width; i++)
            {
                info[i] = new PointInfo[height];
                for (int j = 0; j < height; j++)
                {
                    info[i][j] = new PointInfo();
                }
            }
            return info;
        }

        void assignTactic(PointInfo to, PointInfo from)
        {
            if (from == null) return;
            to.damage = from.damage;
            to.throwGrenage = from.throwGrenage;
            to.grenadeTarget = from.grenadeTarget;
            
            to.shootsCount = from.shootsCount;
            to.shootTarget = from.shootTarget;
            to.eatFieldRation = from.eatFieldRation;
            
            to.shootingStance = from.shootingStance;
            to.retreatStance = from.retreatStance;
        }

        public int getRetreatEnemyDamage(PointInfo pi)
        {
            return pi.enemyDamage[stanceId(pi.retreatStance)];
        }

        bool isBetterTactic(PointInfo better, PointInfo worse)
        {
            if (worse == null) return true;
            if (better.damage > worse.damage) return true;
            if (better.damage < worse.damage) return false;
            int betterEnemyDamage = getRetreatEnemyDamage(better);
            int worseEnemyDamage = getRetreatEnemyDamage(worse);
            if (betterEnemyDamage < worseEnemyDamage) return true;
            if (betterEnemyDamage > worseEnemyDamage) return false;
            return better.teammatesProximity > worse.teammatesProximity;
        }

        double bnFactor(double d)
        {
            if (d > valueCriticalDistanceBonus) return 0;
            return 1.0 - (d / valueCriticalDistanceBonus);
        }

        double tmFactor(double d)
        {
            return 1.0 - (d / valueCriticalDistanceTM);
        }

        double tmFactorBattle(double d)
        {
            return 1.0 - (d / valueCriticalDistanceTMBattle);
        }

        double enemyDamageSize(int hp, int damage)
        {
            if (damage == 0) return zeroDamage;
            if (hp <= damage) return killedFactor;
            return hp / damage;
        }

        Move makeMoveTo(ActionType type, Point to)
        {
            Move move = new Move();
            move.Action = type;
            if (to == null)
            {
                move.X = 0;
                return move;
            }
            move.X = to.x;
            move.Y = to.y;
            return move;
        }

        int bonusesAmount(Trooper t)
        {
            int x = 0;
            if (t.IsHoldingMedikit) x++;
            if (t.IsHoldingGrenade) x++;
            if (t.IsHoldingFieldRation) x++;
            return x;
        }

        // 2  3  5
        // 7     11
        // 13 17 19

        int badPositionRate(Point p)
        {
            int pr = 1;
            int count = 0;
            for (int dx = -1; dx < 2; dx++)
                for (int dy = -1; dy < 2; dy++)
                {
                    Point t = p.add(new Point(dx, dy));
                    if (!isInsideWorld(t) || world.Cells[t.x][t.y] != CellType.Free)
                    {
                        count++;
                        pr *= primes[dx + 1][dy + 1];
                    }
                }
            if (count == 2)
            {
                if (pr == 2 * 3 || pr == 3 * 5 || pr == 5 * 11 || pr == 11 * 19 ||
                    pr == 19 * 17 || pr == 17 * 13 || pr == 13 * 7 || pr == 13 * 2)
                    return 1;
            }
            if (count == 4)
            {
                if (pr == 2 * 7 * 5 * 11  || pr == 13 * 7 * 19 * 11 ||
                    pr == 2 * 3 * 13 * 17 || pr == 5 * 3 * 19 * 17)
                    return 2;
            }
            if (count > 2)
            {
                if (pr % 7 * 3 * 11 == 0 || pr % 7 * 3 * 17 == 0 ||
                    pr % 17 * 3 * 11 == 0 || pr % 7 * 11 * 17 == 0)
                    return 3;
            }
            return 0;
        }

        int teamleadPriority(TrooperType type)
        {
            switch (type)
            {
                case TrooperType.Soldier:
                    return 4;
                case TrooperType.Commander:
                    return 5;
                case TrooperType.FieldMedic:
                    return 3;
                default:
                    return 0;
            }
        }

        bool amIteamlead(TrooperType selfType)
        {
            bool am = true;
            foreach (Trooper tr in teammates)
            {
                if (teamleadPriority(tr.Type) > teamleadPriority(selfType))
                {
                    am = false;
                    teamLeadPos = new Point(tr.X, tr.Y);
                }
            }
            return am;
        }

        int visibleTM(Trooper self, Point p)
        {
            int v = 0;
            foreach (Trooper t in teammates)
            {
                if (t.Type != self.Type && 
                    world.IsVisible(self.VisionRange, p.x, p.y, TrooperStance.Prone, t.X, t.Y, TrooperStance.Prone))
                {
                    v++;
                }
            }
            return v;
        }

        int trId(TrooperType type)
        {
            switch (type)
            {
                case TrooperType.Commander: return 5;
                case TrooperType.FieldMedic: return 4;
                case TrooperType.Scout: return 3;
                case TrooperType.Sniper: return 2;
                case TrooperType.Soldier: return 1;
            }
            return 0;
        }

    }
}
