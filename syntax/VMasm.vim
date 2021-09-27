" Vim syntax file
" Language: VM assembly
" Maintainer: Itai Nelken
" Latest Revision: 26 September 2021

if exists("b:current_syntax")
	finish
endif

" Keywords
syn keyword VMKeyword push pop peek add sub mul div set pset get jmp jeq jlt jgt mov nop hlt
syn keyword VMKeyword PUSH POP PEEK ADD SUB MUL DIV SET PSET GET JMP JEQ JLT JGT MOV NOP HLT

" Registers
syn keyword Reg a b c d e f sp pc
syn keyword Reg A B C D E F SP PC
syn match VMRegister "R.*$" contains=Reg

" Numbers
syn match VMNumber "\v\-?\d*(\.\d+)?"

" Comments
syn match VMComment "\v;.*.$"

ley b:current_syntax="VMasm"
highlight def link VMKeyword Keyword
highlight def link VMRegister Number
highlight def link VMNumber Number
highlight def link VMComment Comment

