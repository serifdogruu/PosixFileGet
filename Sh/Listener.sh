#!/usr/bin/expect
#!/bin/sh
# Zaman aşımı süresi
set timeout 10

# ADB shell komutu ile cihaza bağlan
spawn adb shell

# login: ifadesini bekle ve kullanıcı adını gir
expect "login:"
send "root\r"

# Password: ifadesini bekle ve şifreyi gir
expect "Password:"
send "quectel123\r"

expect ":"



send "while true; do cat realtimesave.txt; sleep 2; done\r"

interact