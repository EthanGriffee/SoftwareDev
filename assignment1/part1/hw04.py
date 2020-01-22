import sys

def scan(input_file, starting_line):
    longest_row_number = 0
    longest_row_length = starting_line
    longest_row_dict = []
    every_row_dict = []
    # check startingline + 500 isnt eof
    for i in range(0, XXXXX):
        row = input_file.readline()
        curr_char = 0
        row_length = 0
        row_dict = []
        while curr_char < len(row):
            def scan_digits():
                curr_char += 1
                while row[curr_char].isdigt():
                    curr_char += 1

            if row[curr_char] == "<":
                curr_char += 1
                while row[curr_char] == " ":
                    curr_char += 1
            else:
                error
                
            if row[curr_char] == "\"":
                curr_char += 1
                end_char = row.find("\"", curr_char)
                if end_char - curr_char < 255 and end_char != -1:
                    curr_char = end_char
                    row_dict[row_length] = "STRING"
                else:
                    error

            elif row[curr_char] == "1" or row[curr_char] == "0":
                if row[curr_char + 1] == " " or row[curr_char + 1] == ">":
                    curr_char += 1
                row_dict[row_length] = "BOOL"
            
            elif row[curr_char] == "+" or row[curr_char] == "-" or row[curr_char].isdigit():
                scan_digits()
                row_dict[row_length] = "INTEGER"
                if row[curr_char] == ".":
                    scan_digits()
                    row_dict[row_length] = "FLOAT"
            
            elif row[curr_char] == ".":
                scan_digits()
                row_dict[row_length] = "FLOAT"

            elif row[curr_char] != ">":
                curr_char += 1
                end_char = row.find(" ", curr_char)
                end_char2 = row.find(">", curr_char)
                if end_char > end_char2:
                    end_char = end_char2
                if end_char == -1:
                    end_char = end_char2
                if end_char - curr_char < 255 and end_char != -1:
                    curr_char = end_char
                    row_dict[row_length] = "STRING"
                else:
                    error

            while row[curr_char] == " ":
                curr_char += 1
            if row[curr_char] == ">":
                curr_char += 1
                row_length += 1
            else:
                error
        every_row_dict[i] = row_dict
        if row_length > longest_row_length:
            longest_row_length = row_length
            longest_row_number = i
            longest_row_dict = row_dict


                

while x < len(sys.argv):
    flag = sys.argv[x]

    if flag == "-f":
        x += 1
        file_name = sys.argv[x]

    elif flag == "-from":
        x += 1
        starting_pos = sys.argv[x]

    elif flag == "-len":
        x += 1
        num_bytes = sys.argv[x]

    elif flag == "-print_col_type":
        x += 1
        col_num = sys.argv[x]

    elif flag == "-print_col_idx":
        x += 1
        col_num = sys.argv[x]
        x += 1
        row_num = sys.argv[x]

    elif flag == "-is_missing_idx":
        x += 1
        col_num = sys.argv[x]
        x += 1
        row_num = sys.argv[x]
    x += 1

file = open(file_name)
file.seek(starting_pos)