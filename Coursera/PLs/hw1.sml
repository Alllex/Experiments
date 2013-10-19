
(*
   Assignment 1
*)

(* #1 *)
fun is_older (date1 : int * int * int, date2 : int * int * int) =
    let 
        val y1 = (#1 date1)
        val m1 = (#2 date1)
        val d1 = (#3 date1)
        val y2 = (#1 date2)
        val m2 = (#2 date2)
        val d2 = (#2 date2)
    in
        y1 < y2 
        orelse (y1 = y2 andalso m1 < m2)
        orelse (y1 = y2 andalso m1 = m2 andalso d1 < d2)
    end


(* #2 *)
fun number_in_month (ds : (int * int * int) list, m : int) =
    let fun count (ds : (int * int * int) list) = 
            if null ds 
            then 0 
            else (if (#2 (hd ds)) = m 
                  then 1 
                  else 0) + count (tl ds)
    in
        count ds
    end


(* #3 *)
fun number_in_months (ds : (int * int * int) list, ms : int list) = 
    let fun nms (ms : int list) = 
            if null ms 
            then 0 
            else number_in_month(ds, hd ms) + nms(tl ms)
    in
        nms ms
    end

(* #4 *)
fun dates_in_month (ds : (int * int * int) list, m : int) = 
    let 
        fun filter (r : (int * int * int) list) = 
            if null r 
            then [] 
            else let val tail = filter (tl r) 
                 in if (#2 (hd r)) = m 
                    then hd r::tail 
                    else tail
                 end
    in 
        filter ds
    end

(* #5 *)
fun dates_in_months (ds : (int * int * int) list, ms : int list) = 
    let
        fun dim(ms : int list) = 
            if null ms 
            then [] 
            else dates_in_month(ds, hd ms) @ dim (tl ms)
    in
        dim ms
    end

(* #6 *)
fun get_nth (xs : string list, n : int) = 
    if n = 1 then hd xs else get_nth(tl xs, n - 1)

(* #7 *)
fun date_to_string (d : int * int * int) = 
    let 
        val months = ["January","February",
                      "March","April","May",
                      "June","July","August",
                      "September","October","November",
                      "December"]
    in 
        (get_nth(months,#2 d)) ^ " " ^ (Int.toString (#3 d)) ^ ", " ^ (Int.toString (#1 d))
    end

(* #8 *)
fun number_before_reaching_sum (sum : int, xs : int list) = 
    let 
        fun sumIt (acc : int, n : int, xs : int list) = 
            let val t = acc + hd xs 
            in
                if t >= sum 
                then n 
                else sumIt(t, n + 1, tl xs) 
            end
    in 
        sumIt(0,0,xs)
    end

(* #9 *)
fun what_month (day : int) =
    let
        val lengths = [31,28,31,30,31,30,31,31,30,31,30,31]
    in
        number_before_reaching_sum(day,lengths) + 1
    end

(* #10 *)
fun month_range (day1 : int, day2 : int) = 
    let
        fun count_up (day : int) = 
            if day > day2 
            then [] 
            else what_month(day)::count_up(day + 1)
    in
        count_up day1
    end

(* #11 *)
fun oldest (ds : (int * int * int) list) = 
    let 
        fun find_oldest (cur : int * int * int, r : (int * int * int) list) = 
            if null r 
            then cur 
            else find_oldest ((if is_older(cur, hd r) 
                               then cur 
                               else hd r), tl r)
    in
        if null ds 
        then NONE 
        else SOME(find_oldest(hd ds, tl ds))
    end

(* #12 *)

fun remove_duplicates (xs : int list) = 
    let 
        fun elem (x : int, xs : int list) = 
            if null xs 
            then false 
            else x = (hd xs) orelse elem(x, tl xs)

        fun rd (acc : int list, rest : int list) =
            if null rest 
            then acc 
            else if elem(hd rest, acc) 
                 then rd(acc, tl rest) 
                 else rd(hd rest :: acc, tl rest)
                 
    in 
        rd([], xs)
    end

(* #12.1 *)
fun number_in_months_challenge (ds : (int * int * int) list, ms : int list) = 
    number_in_months(ds, remove_duplicates ms)

(* #12.2 *)
fun dates_in_months_challenge (ds : (int * int * int) list, ms : int list) = 
    dates_in_months(ds, remove_duplicates ms)

(* #13 *)
fun reasonable_date(date : int * int * int) = 
    let 
        fun month_length(m : int, y : int) = 
            let 
                fun get_nth (xs : int list, n : int) = 
                   if n = 1 then hd xs else get_nth(tl xs, n - 1)

                val lengths = [31,28,31,30,31,30,31,31,30,31,30,31]
            in 
                if m = 2 andalso (y mod 400 = 0 orelse y mod 4 = 0 andalso y mod 100 <> 0)
                then 29
                else get_nth(lengths, m)
            end
        val y = #1 date
        val m = #2 date
        val d = #3 date
    in
        y > 0 
        andalso m > 0 andalso m <= 12 
        andalso d > 0 andalso d <= month_length(m,y)
    end
