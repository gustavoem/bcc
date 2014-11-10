import ply.lex as lex
import ply.yacc as yacc

tokens = [
   'NUMBER',
   'PLUS',
   'MINUS',
   'TIMES',
   'DIVIDE',
   'VAR',
   'EQUAL']

# Regex para os tokens
t_NUMBER  = r'[0-9]*\.*[0-9]+'
t_PLUS    = r'\+'
t_MINUS   = r'-'
t_TIMES   = r'\*'
t_DIVIDE  = r'/'
t_VAR     = r'[A-z]{1}([A-z]|[0-9])*'
t_EQUAL   = r'='
t_ignore  = ' \t\n' #ignorar tabs e espacos e \n

# Regra para lidar com erros
def t_error(t):
    print("Nao entendi o que voce quis dizer com: '%s'" % t.value[0])
    t.lexer.skip(1)

# instancia o analex
lexer = lex.lex()

var = dict()
# gramatica
def p_expr_equal(p):
    '''expr : expr expr EQUAL'''
    if type(p[1]) is not str:
        print("Atribuicao invalida")
    else:
        var[p[1]] = p[2]
        p[0] = p[1]

def get_value(a):
    if a in var:
        a = var[a]
    return a

def p_expr_plus(p):
    '''expr : expr expr PLUS'''
    p[1], p[2] = get_value(p[1]), get_value(p[2])
    p[0] = p[1] + p[2]

def p_expr_minus(p):
    '''expr : expr expr MINUS'''
    p[1], p[2] = get_value(p[1]), get_value(p[2])
    p[0] = p[1] - p[2]

def p_expr_times(p):
    '''expr : expr expr TIMES'''
    p[1], p[2] = get_value(p[1]), get_value(p[2])    
    p[0] = p[1] * p[2]

def p_expr_divide(p):
    '''expr : expr expr DIVIDE'''
    p[1], p[2] = get_value(p[1]), get_value(p[2])
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

def p_expr_var(p):
    '''expr : VAR'''
    if p[1] in var:
        p[0] = p[1]
    else:
        var[p[1]] = 0
        p[0] = p[1]

def p_error(p):
    print("Ops! Sintaxe invalida")

# instancia o yacc. Os argumentos sao para evitar mensagens de debug
yacc.yacc(debug = 1, write_tables = 1) 
s = 1
while s == 1:
    try:
        line = input("miniep5>: ")
    except EOFError:
        s = 0
    else:
        r = yacc.parse(line)
        if r is not None:
            if r in var:
                print(" " + str(var[r]))
            else:
                print(" " + str(r))
