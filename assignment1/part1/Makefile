docker:


test:
	./sorer -f test.txt -print_col_idx 5 63504 > output.txt
	echo parsing > output_expected.txt
	diff output.txt output_expected.txt

	./sorer -f "data.sor" -from 0 -len 100 -print_col_type 0 > output.txt
	echo BOOL > output_expected.txt
	diff output.txt output_expected.txt

	./sorer -f "data.sor" -from 0 -len 100 -print_col_type 2 > output.txt
	echo STRING > output_expected.txt
	diff output.txt output_expected.txt

	./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 0 > output.txt
	echo False > output_expected.txt
	diff output.txt output_expected.txt

	./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 1 > output.txt
	echo True > output_expected.txt
	diff output.txt output_expected.txt

	./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 2 > output.txt
	echo True > output_expected.txt
	diff output.txt output_expected.txt

	./sorer -f "data.sor" -from 0 -len 100 -print_col_idx 2 0 > output.txt
	echo "hi" > output_expected.txt
	diff output.txt output_expected.txt

	./sorer -f "data.sor" -from 5 -len 100 -print_col_idx 1 0 > output.txt
	echo 12 > output_expected.txt
	diff output.txt output_expected.txt

	./sorer -f "length_test.sor" -from 200 -len 200 -print_col_type 0 > output.txt
	echo STRING > output_expected.txt
	diff output.txt output_expected.txt

	./sorer -f "length_test.sor" -from 236 -len 200 -print_col_idx 0 0 > output.txt
	echo "Go Team" > output_expected.txt
	diff output.txt output_expected.txt



	@rm -f output.txt output_expected.txt
