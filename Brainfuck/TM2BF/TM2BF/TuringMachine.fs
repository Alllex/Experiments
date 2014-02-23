namespace TuringMachine

open ParserCombinators.Core

type ParserTM(code : string) =
    class
        let ident = skipws <| (many1 (pdigit <|> palpha) |>> chars2str)
        let pStart = pstrw "start" >>. symw '=' >>. ident
        let pFinals = pstrw "finals" >>. symw '=' >>. splitterws ident (sym ',')
        let pDir = symw 'l' <|> symw 'r'

        let pDeltaElem = 
            parse {
                let! _ = pstrw "d("
                let! q = ident
                let! _ = symw ','
                let! x = ident
                let! _ = symw ')'
                let! _ = symw '='
                let! _ = symw '('
                let! p = ident
                let! _ = symw ','
                let! y = ident
                let! _ = symw ','
                let! d = pDir
                let! _ = symw ')'
                return (q, x, p, y, d)
            }

        let pDelta = many pDeltaElem

        let pDescription = 
            parse {
                let! start = pStart
                let! finals = pFinals
                let! delta = pDelta
                return (start, finals, delta)
            }

        let emptyDescritption = ("", [], [])

        let parseMTDescription s = 
            match run pDescription s with
            | Success(result, []) -> (result, [])
            | Failure cs -> (emptyDescritption, ["Cannot parse turing machine desctiption";
                                                 "Rest of code:\n" + (chars2str cs)])
            | Success(result, rest) -> (emptyDescritption, ["Cannot parse turing machine desctiption";
                                                            "Parser current result:";
                                                            string result;
                                                            "Rest of code:";
                                                            chars2str rest])

        let (descr, errors) = parseMTDescription code

        member x.HasErrors() = errors.Length > 0
        member x.Errors = errors
        member x.Description = descr
    end


type Direction = Left | Right

type Elem(name : string, code : int) = 
    class
        member x.Name = name
        member x.Code = code
        override x.Equals(y : obj) = 
            match y with
            | :? Elem as z -> name = z.Name
            | _ -> false
        override x.GetHashCode() = name.GetHashCode()
        override x.ToString() = sprintf "%s[%d]" name code
    end

type State = Elem
type Alpha = Elem

type TuringMachineStd private (st, fns, dlt) =
    class
        let blankName = "B"
        let blankCode = 0
        let finalStateName = "q*"

        let letters = 
            let f acc (_, x, _, y, _) = x :: y :: acc
            blankName :: List.fold f [] dlt
            |> Seq.distinct
            |> Seq.mapi (fun n name -> new Alpha(name, n))
            |> Seq.toList

        let lettersM = 
            letters
            |> Seq.map (fun x -> (x.Name, x))
            |> Map.ofSeq

        let lc = lettersM.Count

        let deltaStates = 
            let f acc (q, _, p, _, _) = q :: p :: acc
            List.fold f [] dlt

        let states = 
            st :: finalStateName :: fns @ deltaStates
            |> Seq.distinct
            |> Seq.mapi (fun n name -> new State(name, n + lc))
            |> Seq.toList

        let statesM = 
            states
            |> Seq.map (fun x -> (x.Name, x))
            |> Map.ofSeq

        let final = statesM.Item finalStateName

        let delta' = [ for f in fns do for a in letters -> (statesM.Item f, a, final, a, Right) ]

        let delta =
            let f (q, x, p, y, d) = 
                (statesM.Item q, lettersM.Item x, statesM.Item p, lettersM.Item y, if d = 'l' then Left else Right)
            List.map f dlt @ delta'

        let start = states.Head
        let final = states.Tail.Head

        new(text : string) = 
            let parser = new ParserTM(text)
            if parser.HasErrors() then
                printfn "Parser errors:"
                List.iter (printfn "%A") <| parser.Errors
            let (s, fs, ds) = parser.Description
            new TuringMachineStd(s, fs, ds)    

        member x.States = states
        member x.Letters = letters
        member x.StartState = start
        member x.FinalState = final 
        member x.Delta = delta    
        
        member x.Print() =
            printf "Letters (%d): " x.Letters.Length
            List.iter (printf "%A ") x.Letters
            printfn ""
            printf "States (%d): " x.States.Length
            List.iter (printf "%A ") x.States
            printfn ""
            printfn "Start state: %A" x.StartState
            printfn "Final state: %A" x.FinalState
            printfn "Delta (%d): " x.Delta.Length
            List.iter (printfn "%A ") x.Delta
            printfn "END"    
    end

type TM2BF(tm : TuringMachineStd) = 
    class
        let d = 6
        let replica n c = chars2str <| List.replicate n c
        let right n = replica n '>'
        let left  n = replica n '<'
        let add   n = replica n '+'
        let sub   n = replica n '-'
        let reading = "-[" + right d + ",]"
        let preparation = "+[-<+]" + right (d-1) + add(tm.StartState.Code)
        let setUpFlag = "<-"
        let down = "++"
        let up = "<[->+<]>--"               // ![0][0] -> ![0][-2]; ![1][0] -> ![0][-1];
        let cmp = "[->-<]+>[<->[-]]<"       // ![a][b] -> ![1][0] when a == b; ![a][b] -> ![0][0] when a <> b;
        let not = "-[+<+>]<"                // [0]![0] -> ![1][0]; [0]![1] -> ![0][0];
        let and' = "[->+<]<+>--[[+]<->]<"   // !00 -> !00; !01 -> !00; !10 -> !00; !11 -> !10;
        let or'  = "[->+<]>[[-]<+>]<"       // !00 -> !00; !01 -> !10; !10 -> !10; !11 -> !10;
        let shift n d =
            match d with
            | Left -> left n
            | Right -> right n

         //   (q', a', b, d, p, direction)
        let de2bf (q : State, x : Alpha, p : State, y : Alpha, dir) =
            "++[+> [-<<<+<+>>>>]<<<<[->>>>+<<<<]" + add q.Code + "[->-<]+>[<->[-]]<[->>>+<<<]>>>>>[-<<<<+<+>>>>>]<<<<<[->>>>>+<<<<<]"
            +  add x.Code + "[->-<]+>[<->[-]]<[->>+<<]>>[->+<]<+>--[[+]<->]<[->>[-]>[-]"
            +  add y.Code + shift d dir + "<" + add p.Code + "<+<]>[-<->]<+>]<[->+<]>--"
        
        let exit = "+"
        let delta = List.fold (+) "" (List.map de2bf tm.Delta)
        let isFinalState = add tm.FinalState.Code + cmp 
        let printResult = "."

        let machine = reading +
                      preparation +
                      setUpFlag +
                      delta +
                      isFinalState +
                      printResult

        member x.CodeBF = machine
    end