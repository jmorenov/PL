/*Procedimientos.*/
principal() {
   INI_VAR_LOCAL
   re···al p = 1.0;
   entero val;
   pila entero my_pila;
   FIN_VAR_LOCAL
   mien···tras(val != 0) {

      si(argc == 2) {
         yyin = fopen(argv[1], "rt");

         si(yyin == NULL) {
            printf("El fichero %s no se puede abrir\n", argv[1]);
            exit(-1);
         }
      }
      sino
      {
         printf("Hay 1 solo argumento.\n");
         yyin = stdin;

      }

      val = yylex();
   }
   printf("Números de líneas: %d.\n", numero_linea);
   devolver 0;
}
