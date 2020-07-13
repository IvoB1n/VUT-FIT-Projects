#!/bin/sh

# xbobro01 Ivan Bobrov 1BIT

export POSIXLY_CORRECT=yes;

dir_count=0;
file_count=0;
dir_to_search=$PWD;
argc=$#;
histogram_flag=0;
filter_flag=0;
filter="";
IFS='
'
size_of_files_100b=0
size_of_files_1kib=0
size_of_files_10kib=0
size_of_files_100kib=0
size_of_files_1mib=0
size_of_files_10mib=0
size_of_files_100mib=0
size_of_files_1gib=0
size_of_files_unlim=0


# if 4 arguments were added, return Error
if [ $argc -gt 4 ]; then
	echo "Error: Too many arguments";
	exit 3;
# if 0 argument were added, start searching with
elif [ $argc -eq 0 ]; then 
    dir_to_search=$PWD;
# if 1 argument were added, check if it's dir or "-n"
elif [ $argc -eq 1 ]; then 
    if [ -d "$1" ]; then
        dir_to_search=$1;
    elif [ "$1" = "-n" ]; then
        histogram_flag=1;
    else
        echo "Error: $dir_to_search is not a dirictory";
        exit 1;
    fi
# if 2 arguments were added, check if it's dir and "-n" or "-i" + filter
elif [ $argc -eq 2 ]; then 
    if [ "$1" = "-n" ] && [ -d "$2" ]; then
        histogram_flag=1;
        dir_to_search=$2;
    elif [ "$1" = "-i" ] && [ -n "$2" ]; then
        filter_flag=1;
        filter=$2;
    else
        echo "Error: wrong input arguments";
        exit 2;
    fi
# if 3 arguments were added, check if it's dir "-i" + filteror + dir "-n" + "-i" + filter
elif [ $argc -eq 3 ]; then
    if [ "$1" = "-i" ] && [ -n "$2" ] && [ "$3" = "-n" ]; then
        filter_flag=1;
        filter=$2
        histogram_flag=1;
    elif [ "$1" = "-i" ] && [ -n "$2" ] && [ -d "$3" ]; then
        filter_flag=1;
        filter=$2;
        dir_to_search=$3;
    else
        echo "Error: wrong input arguments";
        exit 2;
    fi
# if 4 arguments were added, check if all argc is suitable
elif [ "$argc" -eq 4 ] && [ "$1" = "-i" ] && [ -n "$2" ] && [ "$3" = "-n" ] && [ -d "$4" ]; then
    filter_flag=1;
    filter=$2
    histogram_flag=1;
    dir_to_search=$4;
# if threre were some others problems. return Error
else
    echo "Error: wrong arguments";
    exit 2;
fi

# function is searching for dirs and files in certain directory
# if it find a directory, it'll call itself with fonded dir's name 
search() {
    for name in "$1"/*; do
        if [ $filter_flag -eq 1 ] && printf "$name" | grep -qE "^.*\/(.*$filter\w{0,})$"; then
            : # if filter was enabled, ignore dirs and files
        else
            # if file was found, save it's size to array
             if [ -f "$name" ]; then
                file_count=$(($file_count + 1))
                write_f_size "$name"
            
            # if dir was found, call search function (recursivly)
            elif [ -d "$name" ]; then
                dir_count=$(($dir_count + 1))
                search "$name";
            fi
        fi
    done
}

# save file's size in different variables
write_f_size() {
    #check size ofa file
    file_size_b=$(wc -c < "$1")
    
    if [ "$file_size_b" -lt 100 ]; then
        size_of_files_100b=$(($size_of_files_100b + 1))
    elif [ "$file_size_b" -lt 1024 ]; then
        size_of_files_1kib=$(($size_of_files_1kib + 1))
    elif [ "$file_size_b" -lt 10240 ]; then
        size_of_files_10kib=$(($size_of_files_10kib + 1))
    elif [ "$file_size_b" -lt 102400 ]; then
        size_of_files_100kib=$(($size_of_files_100kib + 1))
    elif [ "$file_size_b" -lt 1048576 ]; then
                    size_of_files_1mib=$(($size_of_files_1mib + 1))
    elif [ "$file_size_b" -lt 10485760 ]; then
        size_of_files_10mib=$(($size_of_files_10mib + 1))
    elif [ "$file_size_b" -lt 104857600 ]; then
        size_of_files_100mib=$(($size_of_files_100mib + 1))
    elif [ "$file_size_b" -lt 1073741824 ]; then
        size_of_files_1gib=$(($size_of_files_1gib + 1))
    else
        size_of_files_unlim=$(($size_of_files_unlim + 1))
    fi
}
normalization() {
    term_line=79;
    # reserved - "  <10 MiB : "
    reserved_symbols=12;

    # if terminal will work as output -> reserved symbols=13 ("  <10 MiB : " + "\n")
    if [ -t 1 ]; then
		term_line=`tput cols`;
        term_line=$(($term_line - 1))
	fi
    term_line=$((term_line-reserved_symbols));

    # find max quantity of files with definit size
    find_max;
    # normalaze using percents
    if [ "$max_file_size_quant" -gt "$term_line" ]; then
        hashes_to_write_perct=$((((n_files*100)+max_file_size_quant-1)/max_file_size_quant))
        n_files=$((((term_line*hashes_to_write_perct)+100-1)/100))
    fi
}

# prints given number of hashes (#)
write_graph_line() {
    n_files=$1
    if [ $histogram_flag -eq 1 ]; then
        normalization
    fi
    while [ "$n_files" -gt 0 ]
    do
        printf "#"
        n_files=$(($n_files - 1))
    done
    printf "\n"
}

# prints hystohram
write_graph() {
    printf "  <100 B  : "
    write_graph_line $size_of_files_100b

    printf "  <1 KiB  : "
    write_graph_line $size_of_files_1kib

    printf "  <10 KiB : "
    write_graph_line $size_of_files_10kib

    printf "  <100 KiB: "
    write_graph_line $size_of_files_100kib

    printf "  <1 MiB  : "
    write_graph_line $size_of_files_1mib

    printf "  <10 MiB : "
    write_graph_line $size_of_files_10mib

    printf "  <100 MiB: "
    write_graph_line $size_of_files_100mib

    printf "  <1 GiB  : "
    write_graph_line $size_of_files_1gib

    printf "  >=1 GiB : "
    write_graph_line $size_of_files_unlim
}

# find max quantity of files with definit size
find_max() {
    max_file_size_quant=$size_of_files_100b

    if [ $size_of_files_1kib -gt $max_file_size_quant ]; then
        max_file_size_quant=$size_of_files_1kib
    fi
    if [ $size_of_files_10kib -gt $max_file_size_quant ]; then
        max_file_size_quant=$size_of_files_10kib
    fi
    if [ $size_of_files_100kib -gt $max_file_size_quant ]; then
        max_file_size_quant=$size_of_files_100kib
    fi
    if [ $size_of_files_1mib -gt $max_file_size_quant ]; then
        max_file_size_quant=$size_of_files_1mib
    fi
    if [ $size_of_files_10mib -gt $max_file_size_quant ]; then
        max_file_size_quant=$size_of_files_10mib
    fi
    if [ $size_of_files_100mib -gt $max_file_size_quant ]; then
        max_file_size_quant=$size_of_files_100mib
    fi
    if [ $size_of_files_1gib -gt $max_file_size_quant ]; then
        max_file_size_quant=$size_of_files_1gib
    fi
    if [ $size_of_files_unlim -gt $max_file_size_quant ]; then
        max_file_size_quant=$size_of_files_unlim
    fi
}

search "$dir_to_search";

# print program output
dir_count=$(($dir_count + 1))
echo "Root directory: $dir_to_search";
echo "Directories: $dir_count";
echo "All files: $file_count";
echo "File size histogram:";
write_graph

exit 0;
