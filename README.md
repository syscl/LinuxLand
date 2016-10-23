# Ubuntu-M3800

Hola, this project is targeting for making Ubuntu on M3800 easy to use. And also, the deploy will make the Ubuntu more Apple-like. I will place optimizations for Ubuntu on both M3800 and XPS15 9530, wish you all enjoy it.

Don't hesitate to suggest if you have any good ideas.

---
How to use?

Dowload this project by typing:
```sh
git clone https://github.com/syscl/Ubuntu-M3800
```
This will download the whole directory, the next step is to change the deploy permission so that it can be executed:
```sh
cd Ubuntu-M3800/
chmod +x *
```
Now we can simple execute deploy by typing:
```sh
./deploy
```

---
```sh
git add file
git commit -m "Contents..."
git remote add origin https://github.com/syscl/Ubuntu-M3800.git
git push -u origin master
```

or use
```sh
git add .
git commit -m "Contents..."
git push -u origin master
```
Pay attention to "Clone or download" --> "Use SSH", for exmpale "git@github.com:syscl/Ubuntu-M3800.git"
then, typing:
```sh
git remote set-url origin git@github.com:syscl/Ubuntu-M3800.git
```
