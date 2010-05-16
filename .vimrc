set cindent shiftwidth=8 number incsearch tabstop=8 nowrap
colorscheme desert
autocmd FileType cpp set cindent
autocmd FileType pas runtime indent/pascal.vim 
syn on
map <F5> o/*dbg*/printf("\n");4hi
map! <F5> o/*dbg*/printf("\n");4hi
map <F6> $a		/*  */2hi 
map! <F6> $a		/*  */2hi 
map <F7> o/*  */2hi
map! <F7> o/*  */2hi
map <F9> :%s:\([/{]\)\*dbg\*\([/}]\)\([^{/].*$\):\1\*dbg\*\2\1\1\3\2\2:g
map! <F9> :%s:\([/{]\)\*dbg\*\([/}]\)\([^{/].*$\):\1\*dbg\*\2\1\1\3\2\2:g
map <F11> :g/\/\*dbg\*\//,d
map! <F11> :g/\/\*dbg\*\//,d 
