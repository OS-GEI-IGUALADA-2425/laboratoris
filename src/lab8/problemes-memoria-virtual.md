# Problemes de Memòria Virtual

1. Disposem d'un sistema amb una memòria virtual sota demanda i amb assignació local (4 cel·les per procés). La mida de la pàgina és de 16 paraules. La mida dels enters i de les instrucció és un paraula que equival a 1 Byte. Si exeecutem el programa següent:

```c
main() {
    int i, A[42], B[40];
    A[0] = 0; A[1] = 1;
    for (i = 0; i < 42 i++){
        A[i+2] = A[i] + B[i];
    }
}
```

on el seu conjunt d'instruccions és:

|@(h)  | Codi                               | Comentari       |
|------|------------------------------------|-----------------|
| 0027 | Guardar Mem(@0500)<-0              | A[0] = 0        |
| 0028 | Guardar Mem(@0500 +1)<-0           | A[1] = 0        |
| 0029 | Reg0<-0                            | i=0             |
| 002A | Comparar Reg0,40                   | for             |
| 002B | Salt si Reg0>=40 a 0033            |                 |
| 002C | Carregar Reg1<-Mem(@0500+Reg0)     | Reg1=A[i]       |
| 002D | Carregar Reg2<-Mem(@0600+Reg0)     | Reg2=B[i]       |
| 002E | Reg3<-Reg2+Reg1                    |                 |
| 002F | Reg4<-Reg0+2                       |                 |
| 0030 | Guardar Mem(@0500+Reg4)<-Reg3      | A[i+2]=A[i]+B[i]|
| 0031 | Reg0<-Reg0+1                       | i++             |
| 0032 | Salt a 002A                        |                 |

1. Calcula el nombre de fallades de pàgina que es produeixen en l'execució del programa considerant un algorisme de reemplaçament LRU.

    <details>
    <summary>Mostra la solució</summary>

    El programa necessita carregar el codi amb les instruccions i els seus operands, per tant, necessitem 2 pàgines.

    |@(h)  | Codi                               | Nº de paraules                                            | Pàgina |
    |------|------------------------------------|-----------------------------------------------------------|--------|
    | 0027 | Guardar Mem(@0500)<-0              | 1(instrucció) + 1(operand directe) + 0(operand immediat)  | 2      |
    | 0028 | Guardar Mem(@0500 +1)<-0           | 1(instrucció) + 1(operand directe) + 0(operand immediat)  | 2      |
    | 0029 | Reg0<-0                            | 1(instrucció) + 1(operand directe) + 0(operand immediat)  | 2      |
    | 002A | Comparar Reg0,40                   | 1(instrucció) + 1(operand directe) + 0(operand immediat)  | 2      |
    | 002B | Salt si Reg0>=40 a 0033            | 1(instrucció) + 1(operand directe)                        | 2      |
    | 002C | Carregar Reg1<-Mem(@0500+Reg0)     | 1(instrucció) + 1(operand directe) + 1(operand directe)   | 2      |
    | 002D | Carregar Reg2<-Mem(@0600+Reg0)     | 1(instrucció) + 1(operand directe) + 1(operand directe)   | 2      |
    | 002E | Reg3<-Reg2+Reg1                    | 1(instrucció) + 1(operand directe) + 1(operand directe)   | 3      |
    | 002F | Reg4<-Reg0+2                       | 1(instrucció) + 1(operand directe) + 0(operand immediat)  | 3      |
    | 0030 | Guardar Mem(@0500+Reg4)<-Reg3      | 1(instrucció) + 1(operand directe) + 1(operand directe)   | 3      |
    | 0031 | Reg0<-Reg0+1                       | 1(instrucció) + 1(operand directe) + 0(operand immediat)  | 3      |
    | 0032 | Salt a 002A                        | 1(instrucció) + 1(operand directe)                        | 3      |

    Per tant necessitem 2 pàgines pel codi, assumrem que les pàgines són les següents: 2 i 3, tal com es mostra a la taula anterior.

    | **1:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **50**       | **A[0]...A[15]** |
    |         | **60**       | **B[0]...B[15]** |
    |         |              | **fins A[15]=A[13]+B[13]** |

    | **2:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **51**       | **A[16]...A[31]** |
    |         | **60**       | **B[0]...B[15]** |
    |         |              | **A[16]=A[14]+B[14]** |

    | **3:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **51**       | **A[16]...A[31]** |
    |         | **50**       | **A[0]...A[15]** |
    |         |              | **lectura A[15]** |

    | **4:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **60**       | **B[0]...B[15]** |
    |         | **50**       | **A[0]...A[15]** |
    |         |              | **lectura B[15]** |

    | **5:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **60**       | **B[0]...B[15]** |
    |         | **51**       | **A[16]...A[31]** |
    |         |              | **A[17]=A[15]+B[15]** |

    | **6:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **61**       | **B[16]...B[31]** |
    |         | **51**       | **A[16]...A[31]** |
    |         |              | **lectura B[16]** |

    | **7:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **61**       | **B[16]...B[31]** |
    |         | **52**       | **A[32]...A[47]** |
    |         |              | **A[32]=A[30]+B[30]** |

    | **8:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **51**       | **A[16]...A[31]** |
    |         | **52**       | **A[32]...A[47]** |
    |         |              | **lectura A[31]** |

    | **9:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **51**       | **A[16]...A[31]** |
    |         | **61**       | **B[16]...B[31]** |
    |         |              | **lectura B[31]** |

    | **10:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **52**       | **A[32]...A[47]** |
    |         | **61**       | **B[16]...B[31]** |
    |         |              | **A[33]=A[31]+B[31]** |

    | **11:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **3**        |   |
    |         | **52**       | **A[32]...A[47]** |
    |         | **62**       | **B[32]...B[47]** |
    |         |              | **lectura B[32]** |

    Es produeixen 11 fallades de pàgina.

    </details>

2. Calcula el nombre de fallades de pàgina que es produeixen en l'execució del programa considerant un algorisme de reemplaçament FIFO.

    <details>
    <summary>Mostra la solució</summary>

    | **1:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         |              |   |
    |         |              |   |

    | **2:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **50**       |   |
    |         | **2**        |   |

    | **3:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **60**       |   |
    |         | **50**       |   |
    |         | **2**        |   |

    | **4:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **3**        |   |
    |         | **60**       |   |
    |         | **50**       |   |
    |         | **2**        |   |

    | **5:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **51**       |   |
    |         | **3**        |   |
    |         | **60**       |   |
    |         | **50**       |   |

    | **6:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **51**       |   |
    |         | **3**        |   |
    |         | **60**       |   |

    | **7:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **50**       |   |
    |         | **2**        |   |
    |         | **51**       |   |
    |         | **3**        |   |

    | **8:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **60**       |   |
    |         | **50**       |   |
    |         | **2**        |   |
    |         | **51**       |   |

    | **9:**  | **\#Página** |   |
    |---------|--------------|---|
    |         | **3**        |   |
    |         | **60**       |   |
    |         | **50**       |   |
    |         | **2**        |   |

    | **10:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **51**       |   |
    |         | **3**        |   |
    |         | **60**       |   |
    |         | **50**       |   |

    | **11:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **51**       |   |
    |         | **3**        |   |
    |         | **60**       |   |

    | **12:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **61**       |   |
    |         | **2**        |   |
    |         | **51**       |   |
    |         | **3**        |   |

    | **13:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **52**       |   |
    |         | **61**       |   |
    |         | **2**        |   |
    |         | **51**       |   |

    | **14:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **3**        |   |
    |         | **52**       |   |
    |         | **61**       |   |
    |         | **2**        |   |

    | **15:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **51**       |   |
    |         | **3**        |   |
    |         | **52**       |   |
    |         | **61**       |   |

    | **16:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **51**       |   |
    |         | **3**        |   |
    |         | **52**       |   |

    | **17:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **61**       |   |
    |         | **2**        |   |
    |         | **51**       |   |
    |         | **3**        |   |

    | **18:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **52**       |   |
    |         | **61**       |   |
    |         | **2**        |   |
    |         | **51**       |   |

    | **19:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **3**        |   |
    |         | **52**       |   |
    |         | **61**       |   |
    |         | **2**        |   |

    | **20:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **60**       |   |
    |         | **3**        |   |
    |         | **52**       |   |
    |         | **61**       |   |

    | **21:** | **\#Página** |   |
    |---------|--------------|---|
    |         | **2**        |   |
    |         | **62**       |   |
    |         | **3**        |   |
    |         | **52**       |   |

    Es produeixen 21 fallades de pàgina.
    </details>
