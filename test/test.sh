printf "\n"
printf "================================================================\n"
printf "TEST CASE 1\n"
printf "sortmate /etc/passwd -o a\n"
sortmate /etc/passwd -o a
printf "sort /etc/passwd -o b\n"
sort /etc/passwd -o b
printf "diff a b\n"
diff a b
