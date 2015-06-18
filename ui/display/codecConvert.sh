for file in ./*
do
    iconv -f GBK -t utf-8 "$file" > "${file}.utf8"
done
