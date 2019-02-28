---
header-includes:
	\usepackage{a4wide}
	\usepackage[czech]{babel}
---
# Srovnání účtů
## Řešení
### Algoritmus
Úlohu řeším tak,že se seřadím účty podle peněžní hodnoty a podle poplatku za příjem. A poté postupně po 1 kreditu 
převádím kredity z účtů na nichž je největší obnos na účty, které mají nejnižší poplatek za příjem a zároveň je na nich 
uloženo alespoň o 2 kredity méně než na účtu ze kterého převádím, aby se účty přinejlepším srovnaly. To dělám tak dlouho 
dokud mi nedojdou peníze na převody, nebo účty na které lze peníze převést.

### Složitost
Uspořádání účtů jde se složitostí `0(Nlog(N))`(používám quicksort). Já to dělám dvakrát tedy `O(2Nlog(N))`. Přesouvání 
peněz se děje se složitostí `O(N)`, kdy N je omezeno množstvím peněz na přesuny. Celková složitost je tedy:
```
O(N + Nlog(N))
```
