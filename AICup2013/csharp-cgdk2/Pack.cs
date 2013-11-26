using System;
using System.Collections.Generic;
using System.Linq;
using Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk.Model;

namespace Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk
{
    partial class Pack
    {
        public Pack()
        {
#if ONLINE_JUDGE
#else
            System.IO.File.Delete(@"C:\Users\alllex\Desktop\abc.txt");
#endif 
            initialize();
        }

        public void initialize()
        {
            primes = new int[3][];
            for (int i = 0; i < 3; i++)
            {
                primes[i] = new int[3];
            }
            primes[0][0] = 2;  primes[1][0] = 3;  primes[2][0] = 5;
            primes[0][1] = 7;  primes[1][1] = 1;  primes[2][1] = 11;
            primes[0][2] = 13; primes[1][2] = 17; primes[2][2] = 19;
        }

        public void makeMove(Trooper self, World world, Game game, Move move)
        {
            update(self, world, game);

            write(world.MoveIndex + ") " + self.Type.ToString() + "HP(" + self.Hitpoints + ") AP(" + self.ActionPoints
                        + "); " + self.Stance.ToString() + " at " + pos(self));

            if (self.IsHoldingMedikit || self.IsHoldingGrenade || self.IsHoldingFieldRation)
            write((self.IsHoldingFieldRation ? " [FieldRation]" : "")
                    + (self.IsHoldingGrenade ? " [Grenade]" : "")
                    + (self.IsHoldingMedikit ? " [Medikit]" : ""));

            if (shouldGoToCheckPoint(self))
            {
                turnsWithoutBattle = 0;
                write("Should go to next check point: " + nextCheckPoint());
                lastTrooper = self.Type;
                goToCheckPointStrategy(self);
            }
            else
            {
                if (shouldRecalcStrategy(self))
                {
                    write("Recalc strategy                          **************************");
                    write("Why:" + (isItNewTurn(self) ? " [New turn]" :
                        (isSmthChanged(self) ? " [Something changed]" :
                        (strategy == null || strategy.Count == 0 ? " [Empty strategy]" : " Hm..."))));
                    lastTrooper = self.Type;
                    calcNewStrategy(self);
                    printStrategy(strategy);
                }
                if (nothingToDo(self))
                {
                    write("Decide to go to next check point");
                    goToCheckPointStrategy(self);
                }
            }
            /*
            if (strategy.Count == 0 && self.ActionPoints > 0)
            {
                write("Just go to the team lead");
                justGoToTheTeamLead(self);
            }
            */
            if (strategy.Count == 0)
            {
                write("Strategy is empty in turn");
                move.Action = ActionType.EndTurn;
            }
            else
            {
                assignMove(move, strategy.Dequeue());
            }
        }

        bool shouldGoToCheckPoint(Trooper self)
        {
            return true;
            return enemiesCount == 0 && turnsWithoutBattle > valueWaiting && 
                   amIHealthy(teammates[0]) && amIteamlead(self.Type);
        }

        void justGoToTheTeamLead(Trooper self)
        {
            write("Team lead: " + teamLeadPos);
            //justGoSomewhereStrategy(self, teamLeadPos, 100);
        }
        
        void justGoSomewhereStrategy(Trooper self, Point dest, int length)
        {
            const int maxLenght = 100;
            WayInfo[][] ways = allWays(pos(self), maxLenght);
            Stack<Move> moves = createPath(pos(self), dest, ways);

            int ap = self.ActionPoints;
            ap -= standingUpCost(self.Stance);
            if (ap < game.StandingMoveCost) return;
            strategy = new Queue<Move>();
            concatQueues(strategy, changingStanceMoves(self.Stance, TrooperStance.Standing));
            int mcost = moveCost(self.Stance);
            while (moves.Count > 0 && ap >= mcost && strategy.Count <= length)
            {
                strategy.Enqueue(moves.Pop());
                ap -= mcost;
            }
        }
        
        bool nothingToDo(Trooper self)
        {
            return strategy.Count == 0 && enemiesCount == 0 && amIteamlead(self.Type);
        }

        void goToCheckPointStrategy(Trooper self)
        {
            justGoSomewhereStrategy(self, nextCheckPoint(), 3);
        }
        
        void calcNewStrategy(Trooper self)
        {
            int maxWayLength = (self.ActionPoints - standingUpCost(self.Stance)) / game.StandingMoveCost;
            WayInfo[][] ways = allWays(pos(self), maxWayLength);
            List<Point> reached = reachable(ways);
            pointInfo = initInfo();

            //calcBonusesRelevance(self, ways, reached);
            //calcTeammatesProximity(self, reached);
            //calcHealAbilities(self, ways, reached);
            //calcEnemyAttackDamage(self, reached);
            //calcSelfAttackDamage(self, ways, reached);
            //calcBadPositions(self, reached);

            calcWeights(self.Hitpoints, reached);
            createBestStrategy(self, ways, reached);
        }

        void calcBonusesRelevance(Trooper self, WayInfo[][] ways, List<Point> reached)
        {
            Bonus bestBonus = null;
            double bestRelevance = 0;
            double bestDistance = INF;
            foreach (Bonus bonus in world.Bonuses)
            {
                double relevance = bonusRelevance(self, bonus);
                bool visible = world.IsVisible(self.VisionRange, self.X, self.Y, self.Stance, bonus.X, bonus.Y, TrooperStance.Prone);
                bool relevant = relevance > 0 && (visible || (!visible && ways[bonus.X][bonus.Y].reached()));
                write("Bonus: " + bonus.Type + " at " + new Point(bonus.X, bonus.Y) +
                      "\trelevance: " + relevance + "\trelevant: " + relevant +
                      "\tdistance: " + self.GetDistanceTo(bonus));
                if (relevant && 
                    (bestBonus == null || bestRelevance < relevance || (Math.Abs(bestRelevance - relevance) < eps && bestDistance > self.GetDistanceTo(bonus))))
                {
                    bestBonus = bonus;
                    bestRelevance = relevance;
                    bestDistance = self.GetDistanceTo(bonus);
                }
            }
            if (bestBonus == null)
            {
                write("No relevant bonuses");
                return;
            }
            write("Best bonus: " + bestBonus.Type + " at " + new Point(bestBonus.X, bestBonus.Y) + "\trelevance: " + bestRelevance);
            foreach (Point p in reached)
            {
                double d = p.distanceTo(bestBonus.X, bestBonus.Y);
                pointInfo[p.x][p.y].bonusesProximity += bnFactor(d) * bestRelevance * bonusFactor;
            }
        }

        Point teamCenterPoint(Trooper self)
        {
            int x = 0;
            int y = 0;
            foreach (Trooper tm in teammates)
            {
                x += tm.X;
                y += tm.Y;
            }
            return new Point(x / teamSize, y / teamSize);
        }

        void calcTeammatesProximity(Trooper self, List<Point> reached)
        {
            if (teamSize == 1) return;
            Point teamCenter = teamCenterPoint(self);
            write("Team center: " + teamCenter);
            foreach (Point p in reached)
            {
                double d = p.distanceTo(teamCenter);
                //double k = (enemiesCount > 0) ? tmFactorBattle(d) : tmFactor(d);
                //double vis = visibleTM(self, p) / (teamSize - 1);
                //write("" + p + " d: " + d + "\tk: " + k + "\tvis: " + vis);
                pointInfo[p.x][p.y].teammatesProximity = d;// *teammateNearFactor * vis;
            }
        }

        void calcHealAbilities(Trooper self, WayInfo[][] ways, List<Point> reached)
        {
            foreach (Point p in reached)
            {
                int ap = apAfterRelocation(self.ActionPoints, self.Stance, self.Stance, ways[p.x][p.y].length); 
                if (ap < game.MedikitUseCost && ap < game.FieldMedicHealCost) continue;
                Trooper hurtest = nearbyHurtest(self, p);
                if (hurtest == null) continue;
                calcHealToHurt(self, p, ap, hurtest);
            }
        }

        void calcHealToHurt(Trooper self, Point selfPos, int ap, Trooper hurt)
        {
            if (ap < game.MedikitUseCost && ap < game.FieldMedicHealCost) return;
            int hp = hurt.Hitpoints;
            bool isMe = self.Id == hurt.Id;
            PointInfo pi = pointInfo[selfPos.x][selfPos.y];
            if (self.IsHoldingMedikit && ap >= game.MedikitUseCost &&
                ((isMe && hp < valueCriticalHitpointsSelf) ||
                (!isMe && hp < valueCriticalHitpoints)))
            {
                ap -= game.MedikitUseCost;
                hp += isMe ? game.MedikitHealSelfBonusHitpoints : game.MedikitBonusHitpoints;

                pi.usedMedikit = true;
                pi.heal += isMe ? game.MedikitHealSelfBonusHitpoints : game.MedikitBonusHitpoints;
                pi.healPoint = isMe ? selfPos : pos(hurt);
            }
            if (hp >= 100 || !amIFieldMedic(self) || ap < game.FieldMedicHealCost) return;
            int healsCount = ap / game.FieldMedicHealCost;
            int dHeal = isMe ? game.FieldMedicHealSelfBonusHitpoints : game.FieldMedicHealBonusHitpoints;
            int healedHP = healsCount * dHeal;
            if (hp + healedHP > 100)
            {
                healedHP = 100 - hp;
                healsCount = healedHP / dHeal + (healedHP % dHeal == 0 ? 0 : 1);
            }
            pi.heal += healedHP;
            pi.healsCount = healsCount;
            pi.healPoint = pos(hurt);
        }

        void calcEnemyAttackDamage(Trooper self, List<Point> reached)
        {
            const int enemyAP = 10;
            foreach (Trooper enemy in visibleEnemies)
            {
                Point enemyPos = pos(enemy);
                TrooperStance enemyStance = enemy.Stance;
                foreach (Point p in reached)
                {
                    PointInfo pi = pointInfo[p.x][p.y];
                    int grenadeDamage = maxGrenadeDamage(enemy, enemyPos, enemyAP, p, null);
                    for (int victimStance = 0; victimStance < 3; victimStance++)
                    {
                        int shootDamage = maxShootDamage(enemy, enemyPos, enemyAP, enemyStance, p, stance(victimStance), null);
                        pi.enemyDamage[victimStance] += (shootDamage > grenadeDamage) ? shootDamage : grenadeDamage;
                    }
                }
            }
        }

        void calcSelfAttackDamage(Trooper self, WayInfo[][] ways, List<Point> reached)
        {
            if (enemiesCount == 0 || self.ActionPoints < self.ShootCost) return;
            List<Direction> dirs = dirsList();
            dirs.Add(Direction.CurrentPoint);
            foreach (Point p in reached)
            {
                int x = p.x;
                int y = p.y;
                PointInfo tactic = new PointInfo();
                for (int shootSt = 0; shootSt < 3; shootSt++)
                {
                    TrooperStance shootStance = stance(shootSt);
                    int ap = apAfterRelocation(self.ActionPoints, self.Stance, shootStance, ways[x][y].length);
                    if (ap < self.ShootCost) continue;
                    for (int retreatSt = 0; retreatSt < 3; retreatSt++)
                    {
                        TrooperStance retreatStance = stance(retreatSt);
                        ap -= changeStanceCost(shootStance, retreatStance);
                        if (ap < self.ShootCost) continue;
                        PointInfo tmpTactic = null;

                        foreach (Trooper enemy in visibleEnemies)
                        {
                            Point enemyPos = pos(enemy);
                            if (enemyPos.distanceTo(p) > self.ShootingRange) continue;

                            tmpTactic = new PointInfo();
                            tmpTactic.retreatStance = retreatStance;
                            tmpTactic.shootingStance = shootStance;

                            maxGrenadeDamage(self, p, ap, enemyPos, tmpTactic);
                            //write("Grenade tactic: " + tmpTactic);
                            if (isBetterTactic(tmpTactic, tactic))
                            {
                                write("Point " + p);
                                write("Find better grenade tactic: " + tmpTactic);
                                write("Distance: " + p.distanceTo(tmpTactic.grenadeTarget));
                                assignTactic(tactic, tmpTactic);
                            }

                            tmpTactic = new PointInfo();
                            tmpTactic.retreatStance = retreatStance;
                            tmpTactic.shootingStance = shootStance;

                            maxShootDamage(self, p, ap, shootStance, enemyPos, enemy.Stance, tmpTactic);
                            tmpTactic.damage = realDamage(enemy.Hitpoints, tmpTactic.damage);
                            //write("Shoot tactic: " + tmpTactic);
                            if (isBetterTactic(tmpTactic, tactic))
                            {
                                write("Point " + p);
                                write("Find better shoot tactic: " + tmpTactic);
                                assignTactic(tactic, tmpTactic);
                            }
                        }
                    }
                }
                assignTactic(pointInfo[x][y], tactic);
            }
        }

        int maxGrenadeDamage(Trooper shooter, Point pos, int ap, Point victim, PointInfo pi)
        {
            int maxDamage = 0;
            if (!shooter.IsHoldingGrenade ||
                ap + (shooter.IsHoldingFieldRation ? 3 : 0) < game.GrenadeThrowCost)
            {
                return 0;
            }
            Point grenadeTarget = null;
            List<Direction> dirs = dirsList();
            dirs.Add(Direction.CurrentPoint);
            foreach (Direction d in dirs)
            {
                Point target = victim.add(dtp(d));
                if (isInsideWorld(target) && pos.distanceTo(target) <= game.GrenadeThrowRange)
                {
                    int damage = grenadeDamage(shooter, target);
                    if (damage > maxDamage)
                    {
                        maxDamage = damage;
                        grenadeTarget = target.copy();
                    }
                }
            }
            if (maxDamage > 0 && pi != null)
            {
                if (ap < game.GrenadeThrowCost)
                {
                    pi.eatFieldRation = true;
                }
                pi.throwGrenage = true;
                pi.damage = maxDamage;
                pi.grenadeTarget = grenadeTarget.copy();
            }
            return maxDamage;
        }

        int maxShootDamage(Trooper shooter, Point pos, int ap, TrooperStance shooterStance,
                             Point victim, TrooperStance victimStance, PointInfo pi)
        {
            bool hasFieldRation = shooter.IsHoldingFieldRation;
            if (ap + (hasFieldRation ? 3 : 0) < shooter.ShootCost ||
                !world.IsVisible(shooter.ShootingRange, pos.x, pos.y, shooterStance, victim.x, victim.y, victimStance))
            {
                return 0;
            }
            int nap = hasFieldRation ? ap + 3 : ap;
            int shootCount = nap / shooter.ShootCost;
            int damage = 0;
            switch (shooterStance)
            {
                case TrooperStance.Prone: damage = shooter.ProneDamage * shootCount;
                    break;
                case TrooperStance.Kneeling: damage = shooter.KneelingDamage * shootCount;
                    break;
                case TrooperStance.Standing: damage = shooter.StandingDamage * shootCount;
                    break;
            }
            if (pi != null)
            {
                pi.damage = damage;
                pi.shootsCount = shootCount;
                pi.eatFieldRation = hasFieldRation;
                pi.shootTarget = victim.copy();
            }
            return damage;
        }

        void calcBadPositions(Trooper self, List<Point> reached)
        {
            List<Direction> dirs = dirsList();
            foreach (Trooper tm in teammates)
            {
                if (tm.Type != self.Type)
                {
                    foreach (Direction dir in dirs)
                    {
                        Point p = pos(tm).add(dtp(dir));
                        if (isFree(p)) pointInfo[p.x][p.y].teammatesProximity -= adjacentSalt;
                    }
                }
            }
            foreach (Point p in reached)
            {
                pointInfo[p.x][p.y].badPosition = badPositionRate(p);
            }
        }

        void calcWeights(int hp, List<Point> reached)
        {
            int width = world.Width;
            int height = world.Height;
            weight = new double[width][];
            for (int i = 0; i < width; i++)
            {
                weight[i] = new double[height];
                for (int j = 0; j < height; j++)
                {
                    weight[i][j] = 0;
                }
            }
            foreach (Point p in reached)
            {
                int x = p.x;
                int y = p.y;
                PointInfo pi = pointInfo[x][y];
                //weight[x][y] += pi.bonusesProximity;
                weight[x][y] += tmPrF(pi.teammatesProximity);
                weight[x][y] += pi.heal * healFactor;
                //weight[x][y] += pi.badPosition * badPositionFactor;
                /*
                if (enemiesCount > 0)
                {
                    weight[x][y] += pi.damage * attackFactor;
                    int enemyDamage = getRetreatEnemyDamage(pi);
                    weight[x][y] += enemyDamageSize(hp, enemyDamage) * enemyDamageFactor;
                }
                */
                write("" + p + " w " + pi.r(weight[x][y]) +
                    " \t\tbn: " + pi.r(pi.bonusesProximity) +
                    " \t\ttm: " + pi.r(pi.teammatesProximity) +
                    " \t\thl: " + pi.r(pi.heal * healFactor) +
                    " \t\tdm: " + pi.r(pi.damage * attackFactor) +
                    " \t\ted: " + pi.r(getRetreatEnemyDamage(pi) * enemyDamageFactor));
            }
        }
        
        void createBestStrategy(Trooper self, WayInfo[][] ways, List<Point> reached)
        {
            strategy = new Queue<Move>();
            Point bp = findBestPoint(pos(self), reached);
            PointInfo pi = pointInfo[bp.x][bp.y];
            TrooperStance bts = bestTempStance(self.ActionPoints, self.Stance, pi.shootingStance, ways[bp.x][bp.y].length);
            concatQueues(strategy, changingStanceMoves(self.Stance, bts));
            Stack<Move> moves = createPath(pos(self), bp, ways);
            while (moves.Count > 0)
            {
                strategy.Enqueue(moves.Pop());
            }
            int ap = apAfterRelocation(self.ActionPoints, self.Stance, bts, ways[bp.x][bp.y].length);
            if (pi.heal > pi.damage)
            {
                write("Heal tactic");
                if (pi.usedMedikit)
                {
                    ap -= game.MedikitUseCost;
                    strategy.Enqueue(makeMoveTo(ActionType.UseMedikit, pi.healPoint));
                }
                for (int i = 0; i < pi.healsCount; i++)
                {
                    ap -= game.FieldMedicHealCost;
                    strategy.Enqueue(makeMoveTo(ActionType.Heal, pi.healPoint));
                }
            }
            else if (pi.damage > 0)
            {
                write("Attack tactic");
                ap -= changeStanceCost(bts, pi.shootingStance);
                concatQueues(strategy, changingStanceMoves(bts, pi.shootingStance));
                if (pi.throwGrenage)
                {
                    write("Grenade throw tactic");
                    ap -= game.GrenadeThrowCost;
                    if (pi.eatFieldRation)
                    {
                        ap += 3;
                        strategy.Enqueue(makeMoveTo(ActionType.EatFieldRation, null));
                    } 
                    strategy.Enqueue(makeMoveTo(ActionType.ThrowGrenade, pi.grenadeTarget));
                }
                else
                {
                    write("Shoot tactic");
                    bool eat = false;
                    for (int i = 0; i < pi.shootsCount; i++)
                    {
                        if (!eat && pi.eatFieldRation && ap < 7)
                        {
                            eat = true;
                            strategy.Enqueue(makeMoveTo(ActionType.EatFieldRation, null));
                            ap += 3;
                        }
                        ap -= self.ShootCost;
                        strategy.Enqueue(makeMoveTo(ActionType.Shoot, pi.shootTarget));
                    }
                }
                concatQueues(strategy, changingStanceMoves(pi.shootingStance, pi.retreatStance));
            }
        }
        
        Point findBestPoint(Point start, List<Point> reached)
        {
            int width = world.Width;
            int height = world.Height;
            Point bp = null;
            foreach (Point p in reached)
            {
                if (bp == null || weight[bp.x][bp.y] < weight[p.x][p.y] ||
                    (Math.Abs(weight[bp.x][bp.y] - weight[p.x][p.y]) < eps && 
                     p.distanceTo(start) < bp.distanceTo(start)))
                {
                    bp = p.copy();
                }
            }
            PointInfo pi = pointInfo[bp.x][bp.y];
            write("Best point: " + bp + " weight: " + weight[bp.x][bp.y]);
            write("Enemy damage: " + getRetreatEnemyDamage(pi));
            write("" + pi);
            return bp;
        }
    }
}
