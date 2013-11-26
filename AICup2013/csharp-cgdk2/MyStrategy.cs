using System;
using System.Collections.Generic;
using Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk.Model;

namespace Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk
{
    public sealed class MyStrategy : IStrategy
    {
        static Pack pack = new Pack();

        public void Move(Trooper self, World world, Game game, Move move)
        {
            try
            {
                pack.makeMove(self, world, game, move);
                pack.printMove(move);
                if (!pack.canDoThisMove(self, move.Action))
                {
                    pack.write("No enough action points");
                    move.Action = ActionType.EndTurn;
                }
            }
            catch (Exception e)
            {
                move.Action = ActionType.EndTurn;
                pack.write("########################################################################################################");
                pack.write(e.StackTrace.ToString());
                pack.write(e.Data.ToString());
                pack.write(e.Message);
            }
        }
    }
}