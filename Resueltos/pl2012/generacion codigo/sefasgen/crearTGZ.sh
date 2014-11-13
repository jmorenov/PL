#!/bin/bash
# Script para crear COPIA de SEGURIDAD

if [ $# == 0 ]; then
	echo "Uso: $0 <version>";
	echo "Nombre BAKUP: sefasgen2_v<version>.tgz";
	exit;
fi

tar -T ARCHIVOS.txt -cvzf sefasgen2_v$1.tgz

echo -e "\n\nCreado BAKUP: sefasgen2_v$1.tgz";

cp sefasgen2_v$1.tgz /mnt/win_c/facultad/proyecto/
cp sefasgen2_v$1.tgz /mnt/win_d/bakupPROYECTO/
cp sefasgen2_v$1.tgz /home/otro/proyecto/BAKUP/

echo -e "\n\nCopiado BAKUP a directorios de respaldo"
