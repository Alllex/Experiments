using System;
using System.Collections.Generic;
using System.Linq;
using Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk.Model;

namespace Com.CodeGame.CodeTroopers2013.DevKit.CSharpCgdk
{
    partial class Pack
    {
        public void write(string s)
        {
#if ONLINE_JUDGE
#else
            System.IO.File.AppendAllText(@"C:\Users\alllex\Desktop\abc.txt", s + "\n");
#endif
        }

        void printStrategy(Queue<Move> str)
        {
            if (str == null || str.Count == 0)
            {
                write("Empty strategy");
                return;
            }
            write("Strategy:");
            foreach (Move m in str)
            {
                printMove(m);
            }
            write("-----------------------");
        }

        public void printMove(Move move)
        {
            switch (move.Action)
            {
                case ActionType.EndTurn:
                    write("Decide do nothing; ");
                    break;
                case ActionType.EatFieldRation:
                    write("Eat field ration; ");
                    break;
                case ActionType.Heal:
                    write("Heal to (" + move.X + ", " + move.Y + "); ");
                    break;
                case ActionType.LowerStance:
                    write("Lower stance; ");
                    break;
                case ActionType.RaiseStance:
                    write("Raise stance; ");
                    break;
                case ActionType.Move:
                    write("Move to (" + move.X + ", " + move.Y + "); ");
                    break;
                case ActionType.Shoot:
                    write("Shoot to (" + move.X + ", " + move.Y + "); ");
                    break;
                case ActionType.ThrowGrenade:
                    write("Throw grenade to (" + move.X + ", " + move.Y + "); ");
                    break;
                case ActionType.UseMedikit:
                    write("Use medikit; ");
                    break;
                case ActionType.RequestEnemyDisposition:
                    write("Request disposition; ");
                    break;
            }
        }
    }
}
