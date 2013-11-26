using System;
using System.Collections.Generic;
using System.Linq;
using Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk.Model;

namespace Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk
{
    partial class Pack
    {
        double tmPrF(double d)
        {
            double ex = 5.0 - (10.0 * d / valueCriticalDistanceTM);
            return ex / (1.0 + ex);
        }

        void calcBattleFieldMetrics()
        {

        }
    }
}
