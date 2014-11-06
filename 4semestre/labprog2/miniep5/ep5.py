import ply.lex as lex
import ply.yacc as yacc

tokens = [
   'NUMBER',
   'PLUS',
   'MINUS',
   'TIMES',
   'DIVIDE']

# Regex para os tokens
t_NUMBER  = r'[0-9]*\.*[0-9]+'
t_PLUS    = r'\+'
t_MINUS   = r'-'
t_TIMES   = r'\*'
t_DIVIDE  = r'/'
t_ignore  = ' \t\n' #ignorar tabs e espacos e \n

# Regra para lidar com erros
def t_error(t):
    print("Nao entendi o que voce quis dizer com: '%s'" % t.value[0])
    t.lexer.skip(1)

# instancia o analex
lexer = lex.lex()

# gramatica
def p_expr_plus(p):
    '''expr : expr expr PLUS'''
    p[0] = p[1] + p[2]

def p_expr_minus(p):
    '''expr : expr expr MINUS'''
    p[0] = p[1] - p[2]

def p_expr_times(p):
    '''expr : expr expr TIMES'''
    p[0] = p[1] * p[2]

def p_expr_divide(p):
    '''expr : expr expr DIVIDE'''
    try:
        p[0] = p[1] / p[2]
    except ZeroDivisionError: 
        print("Uma divisao por zero ocorreu. Colocando zero como resultado")
        p[0] = 0

def p_expr_number(p):
    '''expr : NUMBER'''
    if '.' in p[1]:
        p[0] = float(p[1])
    else:
        p[0] = int(p[1])

def p_error(p):
    print("Ops! Sintaxe invalida")

# instancia o yacc. Os argumentos sao para evitar mensagens de debug
yacc.yacc(debug = 0, write_tables = 0) 

s = 1
while s == 1:
    try:
        line = input("miniep5>: ")
    except EOFError:
        s = 0
    else:
        r = yacc.parse(line)
        if r is not None:
            print(" " + str(r))
