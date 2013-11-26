using System;
using System.Collections.Generic;
using Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk.Model;

namespace Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk
{
    partial class Pack
    {
        public readonly Random random = new Random();

        World world = null;
        Game game = null;
        int miniTurnNumber = 0;

        List<Trooper> teammates = null;
        List<Trooper> visibleEnemies = null;

        bool[][] isFreePoint = null;
        double[][] weight = null;

        Queue<Point> checkPoints = null;
        bool areCheckPointsSet = false;

        int turnsWithoutBattle = 0;
        bool teamSizeChanged = false;
        bool enemiesCountChanged = false;
        bool teamHurtCountChanged = false;
        bool bonusesCountChanged = false;
        int bonusesCount = 0;
        int teamHurtCount = 0;
        int teamSize = 0;
        int enemiesCount = 0;
        TrooperType lastTrooper = TrooperType.Commander;
        Point teamLeadPos = null;

        PointInfo[][] pointInfo = null;
        Queue<Move> strategy = null;

        int[][] primes = null;
    }

    class PointInfo
    {
        public double bonusesProximity = 0;
        public double teammatesProximity = 0;
        public double badPosition = 0;

        public int heal = 0;
        public bool usedMedikit = false;
        public Point healPoint = null;
        public int healsCount = 0;

        public bool eatFieldRation = false;
        public Point grenadeTarget = null;
        public Point shootTarget = null;
        public int[] enemyDamage = new int[3];
        public int damage = 0;
        public bool throwGrenage = false;
        public int shootsCount = 0;
        public TrooperStance shootingStance = TrooperStance.Standing;
        public TrooperStance retreatStance = TrooperStance.Standing;

        public override string ToString()
        {
            string s = "";
            s += "[BP: " + r(bonusesProximity) + "]";
            s += "\t[TP: " + r(teammatesProximity) + "]";
            if (heal > 0)
            {
                s += "\t[HEAL: " + heal + "]";
                s += (usedMedikit ? "\t[M]" : "");
                s += "\t[HC: " + healsCount + "]";
            }
            if (damage > 0)
            {
                s += "\t[DM: " + damage + "]";
                if (throwGrenage)
                {
                    s += "\t [G] [GT: " + grenadeTarget + "]";
                }
                s += "\t[ST: " + shootTarget + "]";
                s += "\t[SC: " + shootsCount + "]";
                s += "\t[SS: " + shootingStance + "]";
                s += "\t[RS: " + retreatStance + "]";
            }
            return s;
        }

        public int r(double d)
        {
            return (int) d;
        }
    }

    class WayInfo
    {
        public int length = Pack.INFi;
        public Direction fromDirection = Direction.CurrentPoint;
        public int visualtyFrom = 0;

        public bool reached()
        {
            return length < Pack.INFi;
        }
    }

    class TrooperHurtComparer : IComparer<Trooper>
    {
        public int Compare(Trooper x, Trooper y)
        {
            if (x.Hitpoints == y.Hitpoints) return 0;
            return (x.Hitpoints > y.Hitpoints) ? 1 : -1;
        }
    }

    class PointComparer : IEqualityComparer<Point>
    {

        public bool Equals(Point x, Point y)
        {
            return x.equal(y);
        }

        public int GetHashCode(Point obj)
        {
            return obj.x.GetHashCode() ^ obj.y.GetHashCode();
        }
    }

    class Point
    {
        public int x = 0;
        public int y = 0;

        public Point(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        public Point(Point p)
        {
            this.x = p.x;
            this.y = p.y;
        }

        public double distanceTo(Point p)
        {
            int xRange = x - p.x;
            int yRange = y - p.y;
            return Math.Sqrt(xRange * xRange + yRange * yRange);
        }

        public double distanceTo(int xx, int yy)
        {
            int xRange = x - xx;
            int yRange = y - yy;
            return Math.Sqrt(xRange * xRange + yRange * yRange);
        }

        public Point add(Point p)
        {
            return new Point(x + p.x, y + p.y);
        }

        public Point sub(Point p)
        {
            return new Point(x - p.x, y - p.y);
        }

        public bool equal(Point p)
        {
            return x == p.x && y == p.y;
        }

        public Point copy()
        {
            return new Point(this);
        }

        public bool isAdjacentOrEqual(Point p)
        {
            return distanceTo(p) < 1.03;
        }

        public override string ToString()
        {
            return "(" + x + ", " + y + ")";
        }

    }

}
