# tubesOS
membuat OS yang dapat bekerja dengan MMU yang disediakan<br/>
harus dapat membuat argumen yang benar dalam memanggil MMU<br/>
# aturan
buat file executable dengan ekstensi .ls atau .exe, hal ini untuk menghindari file biner terpush ke repository<br/>
contoh:<br/>
gcc -o OS.ls OS.c<br/>
# github dengan hotspot itb
set proxy itb<br/>
git config --global http.proxy http[s]://username:password@cache.itb.ac.id:8080<br/>
nonaktifkan proxy<br/>
git config --global --unset http.proxy<br/>
cek proxy<br/>
git config --global --get http.proxy<br/>
