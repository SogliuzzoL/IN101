#!/bin/bash

# Répertoire temporaire où générer divers trucs intermédiaires.
TMPDIR=/tmp/

# Là où sont installés les fichiers d'exemple.
GOLDPATH="/home/sogliuzzo-loris/Documents/info/IN101/DM"

# Set, the extended pattern matching features. Requis pour les trims de
# leading et trailing whitespaces.
shopt -s extglob

BOLDTAG="\033[1m"
REDFG="\033[31m"
GREENFG="\033[32m"
ORANGEFG="\033[33m"
UNDERLINETAG="\033[4m"
NORMALTAG="\033[0m"


ECHOCMD="echo -e"


function ckeck_file_existence ()
{
    local SRC_NAME=$1
    if test -f "$SRC_NAME".c ;
    then
        $ECHOCMD $GREENFG"OK "$SRC_NAME".c present."
        return 0
    else
        $ECHOCMD $REDFG"KO "$SRC_NAME".c absent." $NORMALTAG
        return 1
    fi
}


function check_compilation()
{
    local src_name=$1
    GCC_LOG=`gcc -Wall -Wfatal-errors $src_name.c -o $src_name.x`
    if [[ "$?" == 0 ]] ;
    then
        $ECHOCMD $GREENFG"OK compilation "$src_name".c"$NORMALTAG
        if [ "$GCC_LOG" != "" ] ;
        then
            $ECHOCMD $ORANGEFG"WRN compilation warning "$src_name".c"$NORMALTAG
            return 1
        else
            return 0
        fi
    else
        $ECHOCMD $REDFG"KO compilation" $src_name".c" $NORMALTAG
        return 2
    fi
    return 0
}


function generic_run_test_3_args ()
{
    local PROG=$1
    local INPUT1=$2
    local INPUT2=$3
    local INPUT3=$4
    local EXPECTED=$5
    local EXPECTED_RETCODE=$6
    local EXPECTED_ALT=$7
    local EXPECTED_ALT2=$8
    local EXPECTED_ALT3=$9

    $ECHOCMD "Test : $INPUT1 $INPUT2 $INPUT3 expected : $EXPECTED"

    ./"$PROG".x $INPUT1 $INPUT2 $INPUT3 1>$TMPDIR/out.s 2>$TMPDIR/err.s
    RETCODE=$?
    if [ "$EXPECTED_RETCODE" == 0 ] && [ "$RETCODE" != 0 ]
    then
        $ECHOCMD $REDFG"Invalid return code $RETCODE. Stderr :"
        cat $TMPDIR/err.s
        $ECHOCMD $NORMALTAG
    fi

    PREOUT="$(tail -n 2 $TMPDIR/out.s)"
    # Trim trailing space.
    OUT="$(echo -e "${PREOUT}" | sed -e 's/[[:space:]]*$//')"
    if [[ "$EXPECTED_RETCODE" == 0 ]]
    then
    if [ "$OUT" == "$EXPECTED" ] || [ "$OUT" == "$EXPECTED_ALT" ] || [ "$OUT" == "$EXPECTED_ALT2" ] || [ "$OUT" == "$EXPECTED_ALT3" ]
        then
            $ECHOCMD $GREENFG"OK."$NORMALTAG
        else
            $ECHOCMD $REDFG"KO. Got :"
            $ECHOCMD "$OUT" $NORMALTAG
        fi
    else
        # Cas devant générer une erreur proprement gérée.
        if [[ "$RETCODE" != 0 ]]
        then
            $ECHOCMD $GREENFG"OK."$NORMALTAG
        fi
    fi
}



function main_factory ()
{
    ckeck_file_existence factory
    if [ $? == 0 ] ;
    then
      check_compilation factory
      if [ $? == 0 ] ;
      then
        $ECHOCMD $GREENFG"OK prêt à tester factory."$NORMALTAG
      generic_run_test_3_args factory "$GOLDPATH"/ex1.dat 1 0 "0 1
Lien." 0 "1 0
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex1_1.dat 1 0 "0 1
Lien." 0 "1 0
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex1.dat 2 6 "2 1 4 6
Lien." 0 "6 4 1 2
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex1.dat 6 2 "2 1 4 6
Lien." 0 "6 4 1 2
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex1.dat 5 9 "9 7 5
Lien." 0 "5 7 9
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex1.dat 9 5 "9 7 5
Lien." 0 "5 7 9
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex1_1.dat 5 9 "9 7 5
Lien." 0 "5 7 9
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex1_1.dat 9 5 "9 7 5
Lien." 0 "5 7 9
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex1.dat 2 8 "Pas de lien." 0 "Pas de lien."
      generic_run_test_3_args factory "$GOLDPATH"/ex1.dat 8 2 "Pas de lien." 0 "Pas de lien."
      generic_run_test_3_args factory "$GOLDPATH"/ex1_1.dat 8 2 "Pas de lien." 0 "Pas de lien."
      generic_run_test_3_args factory "$GOLDPATH"/ex1_1.dat 2 8 "Pas de lien." 0 "Pas de lien."
      generic_run_test_3_args factory "$GOLDPATH"/ex2.dat 2 8 "Pas de lien." 0 "Pas de lien."
      generic_run_test_3_args factory "$GOLDPATH"/ex2.dat 9 5 "9 7 5
Lien." 0 "5 7 9
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex2.dat 5 9 "9 7 5
Lien." 0 "5 7 9
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex3.dat 0 5 "0 1 5
Lien." 0 "5 1 0
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex3.dat 2 5 "2 1 5
Lien." 0 "5 1 2
Lien." "2 5
Lien." "5 2
Lien."
      generic_run_test_3_args factory "$GOLDPATH"/ex3.dat 5 2 "2 1 5
Lien." 0 "5 1 2
Lien." "2 5
Lien." "5 2
Lien."
      generic_run_test_3_args factory "$GOLDPATH"/ex3.dat 5 3 "Pas de lien." 0 "Pas de lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex3.dat 3 5 "Pas de lien." 0 "Pas de lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex3.dat 2 3 "2 1 3
Lien." 0 "3 1 2
Lien." "-" "-"
      generic_run_test_3_args factory "$GOLDPATH"/ex3.dat 3 2 "2 1 3
Lien." 0 "3 1 2
Lien." "-" "-"
        generic_run_test_3_args factory /tmp/none "" "" "" 255 "" "-" "-"
        generic_run_test_3_args factory "$GOLDPATH"/ex1.dat 8 8 "8
Lien." 0 "8
Lien." "-" "-"
      fi
    fi
}


# ---- Main ----
main_factory
