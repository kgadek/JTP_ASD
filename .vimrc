set cindent shiftwidth=8 number incsearch tabstop=8 nowrap
colorscheme desert
colorscheme mustang
autocmd FileType cpp set cindent
autocmd FileType pas runtime indent/pascal.vim 
syn on
set foldmethod=indent
set foldnestmax=10
set nofoldenable
set foldlevel=1
map <F5> o/*dbg*/printf("\n");4hi
map! <F5> o/*dbg*/printf("\n");4hi
map <F6> $a		/*  */2hi
map! <F6> $a		/*  */2hi
map <F7> o/*  */2hi
map! <F7> o/*  */2hi
map <F9> :%s:\([/{]\)\*dbg\*\([/}]\)\([^{/].*$\):\1\*dbg\*\2\1\1\3\2\2:g:%s://$::
map! <F9> :%s:\([/{]\)\*dbg\*\([/}]\)\([^{/].*$\):\1\*dbg\*\2\1\1\3\2\2:g:%s://$::
map <F11> :g/[/{]\*dbg\*[/}]/,d
map! <F11> :g/[/{]\*dbg\*[/}]/,d
