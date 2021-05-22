# Lab 03 Hill encryption

Az NTL könyvárcsomag használata, Hill kulcs mátrix generálás (C++): [forrás](/Lab_03/example.cpp).

## Excercises

1. Írjunk programot, mely Hill módszerrel titkosít és visszafejt egy tetszőleges szövegállományt. Használjuk az NTL könyvtárcsomagot.
2. Az alábbi titkosított szöveg Hill módszerrel volt rejtjelezve, ahol a blokk méret d = 2 és a titkosítást az angol ábécé 26 betűje felett végezték Határozzuk meg az eredeti szöveget, tudva, hogy a rejtjelezéshez használt kulcs: (6, 13, 7, 8).
AOGWEPOFKHSVRWYUKDAZKVYYNGYPQFKAWROZIEATIYROLMYYOSNRLIACOFJAGIUT
3. A következő titkosított szöveg az outHill.txt állományban van, Hill módszerrel volt rejtjelezve, ahol a blokk méret d = 2 és a titkosítást az angol ábécé 26 kis betűje plusz a szóköz felett végezték (mod 27-el kell számolni!!). Tudva azt, hogy az "pu"-nak "oa" és "or"-nek "we" a rejtjele határozzuk meg az eredeti szöveget.
4. A titkosított állomány Hill módszerrel volt rejtjelezve, ahol a blokk méret d = 2 és a titkosítást a bájtok felett végezték (mod 256-al kell számolni!!). Tudva azt, hogy az "0x28 0x03"-nek "0x09 0xb7" és "0xff 0xd9"-nek "0xac 0xfb" a rejtjele határozzuk meg az eredeti jpeg állományt.
5. Írjunk programot, amely titkosít és visszafejt egy tetszőleges bináris állományt, ahol blokkonként a Hill-256 titkosítót alkalmazzuk, ahol tetszőlegesen lehessen blokkméretet változtatni, és oldjuk meg az utolsó blokk paddingolását, a PKCS#7 padding módot alkalmazva.

## Solution

You need the NTL library. On linux you can install it using the following command:

```bash
> sudo apt-get install libntl-dev
```

When compile the program you need tu use the *-lntl*, like this:

```bash
> g++ lab03-ex05.cpp -o lab03-ex05 -lntl
```
