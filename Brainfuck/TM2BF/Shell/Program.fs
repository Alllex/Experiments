
open System.IO

open TuringMachine
open ASBi

let outputFileName = "bf.bf"

let readFile (fileName : string) = 
    use streamReader = new StreamReader(fileName)
    streamReader.ReadToEnd()

let writeFile (fileName : string, content : string) =
    use streamWriter = new StreamWriter(fileName)
    streamWriter.Write(content)

[<EntryPoint>]
let main argv = 
    if argv.Length > 0 then
        let inputFileName = argv.[0]
        let code = readFile inputFileName
        let tm = new TuringMachineStd(code)
        let codeBF = (new TM2BF(tm)).CodeBF
        let N = tm.Letters.Length + tm.States.Length + 1
        if argv.Length > 1 then
            let args = argv.[1].Split(',')
                       |> Array.map (int)
            let asbi = new ASBi(codeBF, args, N)
            asbi.Interpret()
        else
            let asbi = new ASBi(codeBF, N)
            asbi.Interpret()
    0
