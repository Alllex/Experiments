
(* provided function *)
fun same_string (s1 : string, s2 : string) =
    s1 = s2

(* 1a *)
fun all_except_option (s, lst) = 
    let fun aux (strs,acc) =
        case strs of [] => NONE
        | x::xs => 
            if same_string(s,x) 
            then SOME (acc @ xs) 
            else aux(xs,x::acc)
    in 
        aux(lst,[])
    end

(* 1b *)
fun get_substitutions1 (subs, s) = 
    let fun aux (sub) = 
            case all_except_option(s,sub) of NONE => []
            | SOME lst => lst
    in
        case subs of [] => []
        | x::xs => aux(x) @ get_substitutions1(xs,s)
    end

(* 1c *)
fun get_substitutions2 (subs, s) = 
    let fun aux (sub) = 
            case all_except_option(s,sub) of NONE => []
            | SOME lst => lst

        fun tail (subs,acc) = 
            case subs of [] => acc
            | x::xs => tail(xs, acc @ aux(x))
    in  
        tail(subs,[])
    end

(* 1d *)
fun similar_names (subs,{first=f,middle=m,last=l}) =
    let fun rc(vs) =
            case vs of [] => []
            | x::xs => {first=x,middle=m,last=l}::rc(xs)
    in 
        {first=f,middle=m,last=l} :: rc(get_substitutions1(subs,f))
    end

(* 2 *)
datatype suit = Clubs | Diamonds | Hearts | Spades
datatype rank = Jack | Queen | King | Ace | Num of int 
type card = suit * rank

datatype color = Red | Black
datatype move = Discard of card | Draw 

exception IllegalMove

(* 2a *)
fun card_color (s,_) =
    case s of Diamonds => Red
    | Hearts => Red
    | _      => Black

(* 2b *)
fun card_value (_,r) = 
    case r of Num n => n
    | Ace => 11
    | _   => 10

(* 2c *)
fun remove_card (cs,c,e) = 
    let fun rm (cs) = 
            case cs of [] => raise e
            | x::xs => if x=c then xs else x::rm(xs)
    in 
        rm(cs)
    end

(* 2d *)
fun all_same_color (cards) = 
    case cards of [] => true
    | c::[]     => true
    | c::c2::cs => card_color(c) = card_color(c2) andalso all_same_color(c2::cs)

(* 2e *)
fun sum_cards (cards) = 
    let fun sum (cs,acc) = 
            case cs of [] => acc
            | c::cs => sum(cs,acc + card_value(c))
    in 
        sum(cards,0)
    end

(* 2f *)
fun score (cards,goal) = 
    let val sum = sum_cards(cards)
        val prelim = if (sum > goal) then 3 * (sum - goal) else (goal - sum) 
    in 
        if all_same_color(cards) 
        then prelim div 2 
        else prelim
    end

(* 2g *)
fun officiate (cards,moves,goal) =
    let fun turn (held,moves,cards) =
            case moves of [] => score(held,goal)
            | (Discard c)::ms => 
                let val held' = remove_card(held,c,IllegalMove) 
                in 
                    turn(held',ms,cards) 
                end
            | (Draw)::ms => 
                case cards of [] => score(held,goal)
                | c::cs => if sum_cards(c::held) > goal 
                           then score(c::held,goal) 
                           else turn(c::held,ms,cs)
    in 
        turn([],moves,cards)
    end

(* 3 *)

fun sum_challenge (cs,acc1,acc2) = 
    case cs of [] => (acc1,acc2)
    | (_,Ace)::cs => sum_challenge(cs,acc1 + 1, acc2 + 11)
    | c::cs       => sum_challenge(cs,acc1 + card_value(c), acc2 + card_value(c))

(* 3a'1 *)
fun score_challenge (cards,goal) =
    let val (min_sum,max_sum) = sum_challenge(cards,0,0)
        val prelim = if (min_sum > goal) 
                     then 3 * (min_sum - goal) 
                     else 
                       if max_sum < goal 
                       then (goal - max_sum)  
                       else 0
    in 
        if all_same_color(cards) 
        then prelim div 2 
        else prelim
    end

(* 3a'2 *)
fun officiate_challenge (cards,moves,goal) =
    let fun turn (held,moves,cards) =
            case moves of [] => score_challenge(held,goal)
            | (Discard c)::ms => 
                let val held' = remove_card(held,c,IllegalMove) 
                in 
                    turn(held',ms,cards) 
                end
            | (Draw)::ms => 
                case cards of [] => score_challenge(held,goal)
                | c::cs => 
                    let val (min_sum,_) = sum_challenge(c::held,0,0)
                    in
                        if min_sum > goal 
                        then score_challenge(c::held,goal) 
                        else turn(c::held,ms,cs)
                    end
    in 
        turn([],moves,cards)
    end

(* 3b *)
fun careful_player (cards,goal) = 
    let fun cheat (left,held,card) =
            case held of [] => NONE
            | h::hs => 
                if score(card :: (left @ hs),goal) = 0
                then SOME h
                else cheat (h::left,hs,card)

        fun turn (held,cards) =
            if score(held,goal) = 0 
            then [] 
            else case cards of [] => []
                | c::cs => 
                    if goal - sum_cards(held) > 10 
                    then (Draw)::(turn(c::held,cs))
                    else case cheat([],held,c) of NONE => []
                         | SOME dis => 
                            (let val held' = remove_card(held,dis,IllegalMove)
                             in 
                                (Discard dis)::(Draw)::[]
                             end) handle IllegalMove => []
    in 
        turn([],cards)
    end
