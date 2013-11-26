using System;
using System.Collections.Generic;
using System.Linq;
using Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk.Model;

namespace Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk
{
    partial class Pack
    {
        public const double INF = 100000000.0;
        public const int INFi = 1000;
        public const double eps = 1e-3;

        const int valueCriticalHitpoints = 50;
        const int valueCriticalHitpointsSelf = 70;
        const int valueCriticalEnemyDamage = 100;
        const double valueCriticalDistanceTM = 2.7;
        const double valueCriticalDistanceTMBattle = 1.6;
        const int valueCriticalDistanceBonus = 3;
        const int valueWaiting = 5;
        const int valueCriticalDistanceFromTeam = 2;
        const int averageVisualRange = 7;
        const int averageShootingRange = 7;

        const double checkPointMarkDist = 3;

        const double bonusFactor = 100;
        const double teammateNearFactor = 200;
        const double adjacentFoul = 1 / 2;
        const double enemyDamageFactor = 10;
        const double attackFactor = 200;
        const double healFactor = 200;
        const double killedFactor = -10;
        const double zeroDamage = 200;
        const double adjacentSalt = 100;
        const double badPositionFactor = -100;
    }

}
