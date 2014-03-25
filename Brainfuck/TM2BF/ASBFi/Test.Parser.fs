module Test

open NUnit.Framework
open ASBi

let ast s = (new ASBi.ParserBF(s)).AST

[<TestFixture>]
type ``Test compilation``() =
    [<Test>]
    member x.``Single characters tests``() =
        Assert.True(ast "+" = List [Chain ['+']; End])
        Assert.True(ast "-" = List [Chain ['-']; End])
        Assert.True(ast "<" = List [Chain ['<']; End])
        Assert.True(ast ">" = List [Chain ['>']; End])
        Assert.True(ast "," = List [Chain [',']; End])
        Assert.True(ast "." = List [Chain ['.']; End])
        Assert.True(ast "*" = ASBi.ParserBF.EmptyAST)
        
    [<Test>]
    member x.``Chains tests``() =
        Assert.True(ast ",> ." = List [Chain [','; '>'; '.']; End])
        Assert.True(ast "+ <-   " = List [Chain ['+'; '<'; '-']; End])
        Assert.True(ast "+++<<<--->>>,,,...#" = ASBi.ParserBF.EmptyAST)
        
    [<Test>]
    member x.``Loops tests`` () = 
        Assert.True(ast "+[+]" = List [Chain ['+']; Loop [Chain ['+']]; End])
        Assert.True(ast "+[<[+]]" = List [Chain ['+']; Loop [Chain ['<']; Loop [Chain ['+']]]; End])
        Assert.True(ast "+[+]]" = ASBi.ParserBF.EmptyAST)
        Assert.True(ast "+[[+]" = ASBi.ParserBF.EmptyAST)

    [<Test>]
    member x.``Addition test``() =
        Assert.True(ast ",>, [-<+>] <." = List [Chain [','; '>'; ',']; Loop [Chain ['-'; '<'; '+'; '>']]; Chain ['<'; '.']; End])

    [<Test>]
    member x.``White space testing``() =
        Assert.True(ast """   
                             +             
                             
                             
                                    +
                                    
                           """ = List [Chain['+'; '+']; End])