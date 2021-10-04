" Vim syntax file
" Language: VM assembly
" Maintainer: Itai Nelken
" Latest Revision: 4 October 2021

if exists("b:current_syntax")
	finish
endif

" Keywords
syn keyword VMKeyword push pop peek add sub mul div set pset get jmp jeq jlt jgt mov nop hlt
syn keyword VMKeyword PUSH POP PEEK ADD SUB MUL DIV SET PSET GET JMP JEQ JLT JGT MOV NOP HLT

" Registers
syn keyword Reg a b c d e f sp pc
syn keyword Reg A B C D E F SP PC
syn match VMRegister "\vR.*"
syntax match VMRegister "\vr.*"

" Numbers
syntax match VMNumber "\v<\d+>" " any integer number

" Comments
syn match VMComment "\v;.*.$" " ';' until end of line

highlight default link VMKeyword Keyword
highlight default link VMRegister Type
highlight default link VMNumber Number
highlight default link VMComment Comment

let b:current_syntax="VMasm"
