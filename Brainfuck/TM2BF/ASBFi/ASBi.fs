namespace ASBi

open System.Diagnostics
open ParserCombinators.Core

type internal Tape = int list * int * int list

type internal Expr = Chain of char list
                   | Loop of Expr list
                   | List of Expr list
                   | End

type internal TapeBF(N : int) =
    class
        let empty = ([], 0, [])
        let left(l, m, r) = match l with
                            | [] -> ([], 0, m::r)
                            | lh::ls -> (ls, lh, m::r)
        let right(l, m, r) = match r with
                             | [] -> (m::l, 0, [])
                             | rh::rs -> (m::l, rh, rs)
        let plus(l, m, r) = (l, (if m = N then -N else m + 1), r)
        let minus(l, m, r) = (l, (if m = -N then N else m - 1), r)
        let comma(l, _, r) x = (l, x, r)
        let dot(_, m, _) = m
        let isZero(_, m, _) = m = 0

        let mutable tape = empty

        member x.Left()  = tape <- left tape
        member x.Right() = tape <- right tape
        member x.Sub()   = tape <- minus tape
        member x.Add()   = tape <- plus tape
        member x.Print() = dot tape
        member x.Read(v) = tape <- comma tape v
        member x.IsCurrectZero() = isZero tape
    end

type internal ParserBF(code : string) =
    class
        let chainChar = any <| List.map symw ['.';',';'+';'-';'<';'>']
        let chain = many1 chainChar |>> Chain

        let rec loop = (between (symw '[') expr (symw ']')) |>> Loop
        and lc = parse { 
                        let! l = loop
                        let! c = chain 
                        return [l; c]
                     }
        and expr = 
            parse {
                let! c = chain
                let! lcs = many lc
                let! ml = opt loop
                return ((List.fold (@) [c] lcs) @ (match ml with None -> [] | Some l -> [l]))
            }

        let pgm = expr |>> (fun e -> List (e @ [End]))

        let emptyProgram = List [End]

        let parseProgram s = 
            match run pgm s with
            | Success(result, []) -> (result, [])
            | _ -> (emptyProgram, ["Cannot parse program"])

        let (ast, errors) = parseProgram code

        member x.HasErrors() = errors.Length > 0
        member x.Errors() = errors
        member x.AST() = ast
    end

type internal Interpreter =
    interface
        abstract member Interpret : unit -> unit
    end

type internal InterpreterInteractive(code : string, N : int) =
    class
        let parser = new ParserBF(code)
        let tape = new TapeBF(N)
        
        let eval_op c =
            match c with
            | '<' -> tape.Left()
            | '>' -> tape.Right()
            | '+' -> tape.Add() 
            | '-' -> tape.Sub()
            | '.' -> printfn "Out: %A" (tape.Print())
            | ',' -> printf  "In:  "; tape.Read(int (System.Console.ReadLine()))
            |  _  -> failwith "Unexpected symbol occured"

        let rec eval expr =
            let evals es = List.iter eval es
            match expr with
            | Chain cs -> List.iter eval_op cs
            | Loop exprs -> if not <| tape.IsCurrectZero() then evals exprs; eval expr
            | List exprs -> evals exprs
            | End -> ()

        interface Interpreter with
            member x.Interpret() = 
                if parser.HasErrors() then
                    printfn "Parser errors:"
                    List.iter (printfn "%A") <| parser.Errors()
                else
                    eval <| parser.AST()
                printfn "END"
    end

type internal InterpreterWithArgs(code : string, args : int [], N : int) =
    class
        let parser = new ParserBF(code)
        let tape = new TapeBF(N)
        let argSize = args.Length
        let mutable argID = 0
        let incID() = argID <- argID + 1
        let eval_op c =
            match c with
            | '<' -> tape.Left()
            | '>' -> tape.Right()
            | '+' -> tape.Add()
            | '-' -> tape.Sub()
            | '.' -> printfn "Out: %A" (tape.Print())
            | ',' -> 
                if argID < argSize then
                    tape.Read(args.[argID])
                    incID() 
                else failwith "Not enough input arguments"
            |  _  -> failwith "Unexpected symbol occured"

        let rec eval expr =
            let evals es = List.iter eval es
            match expr with
            | Chain cs -> List.iter eval_op cs
            | Loop exprs -> if not <| tape.IsCurrectZero() then evals exprs; eval expr
            | List exprs -> evals exprs
            | End -> ()

        interface Interpreter with
            member x.Interpret() = 
                if parser.HasErrors() then
                    printfn "Parser errors:"
                    List.iter (printfn "%A") <| parser.Errors()
                else
                    let stopWatch = Stopwatch.StartNew()
                    eval <| parser.AST()
                    stopWatch.Stop()
                    printfn "%.3f (sec) " stopWatch.Elapsed.TotalSeconds
                printfn "END"
    end

type ASBi private (interpreter : Interpreter) =
    class
        new(code : string, N : int) = new ASBi(new InterpreterInteractive(code, N))
        new(code : string, args : int [], N : int) = new ASBi(new InterpreterWithArgs(code, args, N))

        member x.Interpret() = interpreter.Interpret()
    end