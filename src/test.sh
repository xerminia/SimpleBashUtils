cd cat

./s21_cat -e ../txtfile/*.txt >> ../s21_cat_log.txt

./s21_cat -benstv ../txtfile/*.txt >> ../s21_cat_log.txt

./s21_cat -bn ../txtfile/*.txt >> ../s21_cat_log.txt

./s21_cat --number-nonblank ../txtfile/*.txt >> ../s21_cat_log.txt

./s21_cat -nnnnnn -ssssss -ttttt ../txtfile/*.txt >> ../s21_cat_log.txt

cat -e ../txtfile/*.txt >> ../cat_log.txt

cat -benstv ../txtfile/*.txt >> ../cat_log.txt

cat -bn ../txtfile/*.txt >> ../cat_log.txt

cat -b ../txtfile/*.txt >> ../cat_log.txt

cat -nnnnnn -ssssss -ttttt ../txtfile/*.txt >> ../cat_log.txt

cd ../grep

./s21_grep -e qw ../txtfile/*.txt >> ../s21_grep_log.txt
grep -e qw ../txtfile/*.txt >> ../grep_log.txt

./s21_grep -e qw ../txtfile/*.txt >> ../s21_grep_log.txt
grep -e qw ../txtfile/*.txt >> ../grep_log.txt

./s21_grep -e qw ../txtfile/*.txt -i >> ../s21_grep_log.txt
grep -e qw ../txtfile/*.txt -i >> ../grep_log.txt

./s21_grep -e qw ../txtfile/*.txt -v >> ../s21_grep_log.txt
grep -e qw ../txtfile/*.txt -v >> ../grep_log.txt

./s21_grep -e qw ../txtfile/*.txt -c >> ../s21_grep_log.txt
grep -e qw ../txtfile/*.txt -c >> ../grep_log.txt

./s21_grep -e qw ../txtfile/*.txt -l >> ../s21_grep_log.txt
grep -e qw ../txtfile/*.txt -l >> ../grep_log.txt

./s21_grep -e [a-z] ../txtfile/2.txt -n >> ../s21_grep_log.txt
grep -e [a-z] ../txtfile/2.txt -n >> ../grep_log.txt

./s21_grep -he a ../txtfile/2.txt >> ../s21_grep_log.txt
grep -he a ../txtfile/2.txt >> ../grep_log.txt

./s21_grep -se a ../txtfile/2.txt >> ../s21_grep_log.txt
grep -se a ../txtfile/2.txt >> ../grep_log.txt

./s21_grep -f ../txtfile/test.txt ../txtfile/test.txt >> ../s21_grep_log.txt
grep -f ../txtfile/test.txt ../txtfile/test.txt >> ../grep_log.txt

./s21_grep -ove a ../txtfile/2.txt >> ../s21_grep_log.txt
grep -ove a ../txtfile/2.txt >> ../grep_log.txt
