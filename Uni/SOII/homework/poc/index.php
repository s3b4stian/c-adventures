<?php

$columns = 40;

$array = mb_split(' ',file_get_contents("input.txt"));

$size = count($array);

$j = 0;
$final_array = [];

$row_len = 0;
$tmp_string = [];

function populate_array($columns, $current_word, &$j, &$final_array, &$row_len, &$tmp_string, $new_line = 0){
    
    //var_dump($tmp_string);

    // if there is a new line but isn't a new paragraph
    if ($new_line === 1) {
        //unset($tmp_string[count($tmp_string)-1]);

        $final_array[$j++] = justify_row($tmp_string);
        // restart in a new line
        $row_len = mb_strlen($current_word) + 1;
        $tmp_string = [$current_word, "\x20"];
        return;
    }

    // if it is a new paragraph
    if ($new_line === 2) {
        //unset($tmp_string[count($tmp_string)-1]);

        $final_array[$j++] = $tmp_string;
        $final_array[$j++] = [str_repeat("\x20",30)];

        $row_len = mb_strlen($current_word) + 1;
        $tmp_string = [$current_word, "\x20"];
        return;
    }

    //check the lenght of a the current word
    //ad one for the space at the end
    $row_len += mb_strlen($current_word) + 1;

    if (!is_array($tmp_string)) {
        $tmp_string = [];
    }

    //if the word has enought space to enter in
    //the current row, put it in
    if ($row_len <= $columns) {
        $tmp_string[] = $current_word;
        $tmp_string[] = "\x20";
    }
    //else, start a new row with the current
    //word as first
    else {
        //unset($tmp_string[count($tmp_string)-1]);
        //add line
        $final_array[$j++] = justify_row($tmp_string);
        // restart in a new line
        $row_len = mb_strlen($current_word) + 1;
        $tmp_string = [$current_word, "\x20"];
    }
}


function justify_row($array_row) {
    global $columns;

    unset($array_row[count($array_row)-1]);

    $len_words = 0;
    $words_in_row = 0;
    foreach ($array_row as $r_key => $word) {
        if ($word !== "\x20"){
            $words_in_row++;
        }
        $len_words += mb_strlen($word);
    }

    $spaces_needed = $columns - $len_words;

    if ($words_in_row < 2) {
        return $array_row;
    }

    while ($spaces_needed) {
        foreach ($array_row as $r_key => $word) {
            if (mb_strlen($word) === 0) {
                continue;
            }

            if ($word[0] === "\x20") {
                $array_row[$r_key] .= ' ';
                $spaces_needed--;
            }
            
            if ($spaces_needed === 0){
                break;
            }
        }
    }

    return $array_row;
}

for ($i = 0; $i < $size; $i++) {

    $current_word = $array[$i];

    if ($current_word === '') {
        continue;
    }

    //number of new lines in current word
    //word splitted using spaces
    $numeber_new_lines = mb_substr_count($current_word, "\n");

    if ($numeber_new_lines > 0) {

        $tmp_words = mb_split("\n", $current_word);
        $s_tmp_words = count($tmp_words);

        //only a return
        if ($numeber_new_lines === 1) {
            populate_array($columns, $tmp_words[0], $j, $final_array, $row_len, $tmp_string);
            populate_array($columns, $tmp_words[1], $j, $final_array, $row_len, $tmp_string, 1);
        }
        //paragraph change
        else if ($numeber_new_lines > 1) {
            populate_array($columns, $tmp_words[0], $j, $final_array, $row_len, $tmp_string);
            populate_array($columns, $tmp_words[$s_tmp_words-1], $j, $final_array, $row_len, $tmp_string, 2);
        }
        continue;
    }

    populate_array($columns, $current_word, $j, $final_array, $row_len, $tmp_string);
}

var_dump($final_array);

/*
foreach ($final_array as $key => $row){

    $len_words = 0;
    $words_in_row = 0;
    foreach ($row as $r_key => $word) {
        if ($word !== "\x20"){
            $words_in_row++;
        }
        $len_words += mb_strlen($word);
    }

    $spaces_needed = $columns - $len_words;

    //eccezione per ultima riga paragrafo
    if (isset($final_array[$key+1])) {
        $r = $final_array[$key+1];
        $w = $r[0];
        if ($w[0] === "\x20") {
            continue;
        }
    }

    if ($words_in_row < 2) {
        continue;
    }

    while ($spaces_needed) {
        foreach ($row as $r_key => $word) {
        
            //var_dump($row[$r_key]);
            if ($word[0] === "\x20") {
                //var_dump($row[$r_key]);
                $final_array[$key][$r_key] .= ' ';
                $spaces_needed--;
            }
            
            if ($spaces_needed === 0){
                break;
            }
        }
    }
}*/

/*foreach ($final_array as $key => $row) {
    $row_len = mb_strlen($row);

    if ($row_len < $columns) {
        $final_array[$key] .= str_repeat("\x20", $columns - $row_len);
        $final_array[$key] = '|'.$final_array[$key].'|';
    }
}*/

echo '<pre>';
foreach ($final_array as $key => $row) {
    echo implode('',$row).'<br/>';
}
echo '</pre>';

//var_dump($final_array);
//var_dump($size, $array);