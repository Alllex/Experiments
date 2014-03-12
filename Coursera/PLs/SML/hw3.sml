
(* provided code *)
exception NoAnswer

datatype pattern = Wildcard
         | Variable of string
         | UnitP
         | ConstP of int
         | TupleP of pattern list
         | ConstructorP of string * pattern

datatype valu = Const of int
          | Unit
          | Tuple of valu list
          | Constructor of string * valu

fun g f1 f2 p =
    let 
    val r = g f1 f2
     
    in
    case p of
        Wildcard          => f1 ()
      | Variable x        => f2 x
      | TupleP ps         => List.foldl (fn (p,i) => (r p) + i) 0 ps
      | ConstructorP(_,p) => r p
      | _                 => 0
    end

(* problems *)

(* 1 *)
val only_capitals = List.filter (fn s => Char.isUpper (String.sub(s,0)))
(* 2 *)
val longest_string1 = List.foldl (fn (s,acc) => if String.size s > String.size acc then s else acc) "" 
(* 3 *)
val longest_string2 = List.foldl (fn (s,acc) => if String.size s >= String.size acc then s else acc) ""

(* 4 *)
fun longest_string_helper f = List.foldl (fn (s,acc) => if f(String.size s,String.size acc) then s else acc) ""
val longest_string3 = longest_string_helper (fn (x,y) => x > y)
val longest_string4 = longest_string_helper (fn (x,y) => x >= y)

(* 5 *)
val longest_capitalized = longest_string1 o only_capitals
(* 6 *)
val rev_string = String.implode o List.rev o String.explode

(* 7 *)
fun first_answer f xs = 
    case xs of 
      []     => raise NoAnswer
    | x::xs' => 
        case f x of 
          NONE   => first_answer f xs'
        | SOME b => b

(* 8 *)
fun all_answers f xs = 
    let fun aux(xs,acc) = 
            case xs of 
              []     => acc
            | x::xs' => (case f x of 
                           NONE   => NONE
                         | SOME b => aux(xs', SOME((Option.valOf acc) @ b)))
    in 
        aux(xs, SOME []) 
    end


(* 9 *)
(* 9a *)
val count_wildcards = g (fn () => 1) (fn s => 0)
(* 9b *)
val count_wild_and_variable_lengths = g (fn () => 1) (String.size)
(* 9c *)
fun count_some_var (s,p) = g (fn () => 0) (fn s' => if s = s' then 1 else 0) p

(* 10 *)
fun check_pat p = 
    let fun aux1 acc p = 
            case p of 
              Variable v         => v::acc
            | TupleP ps          => List.foldl (fn (p',acc') => aux1 acc' p') acc ps
            | ConstructorP(_,p') => aux1 acc p'
            | _                  => acc

        fun aux2 (xs : string list) = 
            case xs of 
              []     => true
            | x::xs' => not (List.exists (fn x' => x = x') xs') andalso aux2 xs'
    in
        aux2 (aux1 [] p)
    end

(* 11 *)
fun match (v,p) = 
    case (v,p) of 
      (_,Wildcard)         => SOME []
    | (_,Variable s)       => SOME [(s,v)]
    | (Unit,UnitP)         => SOME []
    | (Const x, ConstP x') => if x = x' then SOME [] else NONE
    | (Tuple vs,TupleP ps) => 
        if List.length vs <> List.length ps 
        then NONE
        else all_answers match (ListPair.zip(vs,ps))

    | (Constructor(s1,v'), ConstructorP(s2,p')) => if s1 <> s2 then NONE else match(v',p')
    | _ => NONE

(* 12 *)
fun first_match v ps = (SOME (first_answer (fn p => match(v,p)) ps)) handle NoAnswer => NONE


(**** for the challenge problem only ****)
datatype typ = Anything
         | UnitT
         | IntT
         | TupleT of typ list
         | Datatype of string
(**** you can put all your code here ****)

fun typecheck_patterns (cs,ps) =
    let fun pattern_type p = 
        case p of 
          Wildcard => Anything
        | Variable _ => Anything
        | UnitP => UnitT
        | ConstP _ => IntT
        | TupleP ps => TupleT (List.map pattern_type ps)
        | ConstructorP(s,_) => (#3 (Option.valOf (List.find (fn (cn,_,_) => cn = s) cs)))

        fun merge_types (t1,t2) = 
            case (t1,t2) of
              (Anything,t)  => t
            | (t,Anything)  => t
            | (UnitT,UnitT) => UnitT
            | (IntT,IntT)   => IntT
            | (Datatype a,Datatype b) => if a = b then Datatype a else raise NoAnswer
            | (TupleT ts,TupleT ts')  => TupleT (List.map merge_types (ListPair.zip(ts,ts')))
            | _ => raise NoAnswer

        fun merge_types_list ct ts = 
            case ts of 
              [] => ct
            | t::ts' => merge_types_list (merge_types (ct,t)) ts'
    in
        (SOME (merge_types_list Anything (List.map pattern_type ps))) handle _ => NONE
    end
