# Install sty
```sh
latex example.ins; latex example.dtx
sudo mkdir /usr/share/texlive/texmf-dist/tex/latex/footmisc
sudo cp example.sty /usr/share/texlive/texmf-dist/tex/latex/footmisc
cd /usr/local/share/texmf/
sudo mktexlsr
```

# Awesome CV support
- Install Xelatex by
```sh
sudo apt install texlive-xetex
```

- Install fontawesome.sty sourcesanspro.sty sourcesanspro-type1-autoinst.sty to ```/usr/share/texlive/texmf-dist/tex/latex/footmisc```

- Place all fonts(FontAwesome, SourceSanspro) to ```/usr/share/fonts/custom```

- Rebuild font cache
