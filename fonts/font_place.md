# The place of fonts that are saved in Ubuntu
```sh
/usr/share/fonts
```
Correct the permission by
```sh
chmod -R 644 [font_repo]/*
chown -R root:root [font_repo]
chmod 755 [font_repo]
```
Do not forget to rebuild font cache once you install fonts by
```sh
sudo fc-cache -f -v
```
