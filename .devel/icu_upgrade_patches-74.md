# ICU 74 Patching Info

## Diffs for ICU 69 (Patches applied in due course)

```bash
COMMIT_ORIGINAL=bbbf25bbe6e1aa198389dd08636a3360b5788213
DIR_ORIGINAL=/tmp/stringi-${COMMIT_ORIGINAL}/src/icu69
DIR_CURRENT=~/R/stringi/src/icu69
DIR_DIFFS=~/R/stringi/.devel/icu69diffs
SUBDIRS=(
    unicode
    common
    i18n
    stubdata
)
```

```bash
cd /tmp
wget https://github.com/gagolews/stringi/archive/${COMMIT_ORIGINAL}.zip
unzip ${COMMIT_ORIGINAL}.zip
```

```bash
shopt -s nullglob
cd ${DIR_CURRENT}
for d in ${SUBDIRS[@]}; do
    mkdir -p ${DIR_DIFFS}/$d
    FILES=(
        ${d}/*.h
        ${d}/*.c
        ${d}/*.cpp
    )

    for f in ${FILES[@]}; do
        diff -u -d -b -B -Z -N ${DIR_ORIGINAL}/$f $f > ${DIR_DIFFS}/$f.diff
        [ -s ${DIR_DIFFS}/$f.diff ] && echo ${DIR_DIFFS}/$f.diff || rm -f ${DIR_DIFFS}/$f.diff
    done
done
```


## Fetch ICU4C

1. Download https://github.com/unicode-org/icu/releases/download/release-74-1/icu4c-74_1-src.zip

2. From the extracted archive, copy source/common, i18n, stubdata to ./src/icu74

3. Move ./src/icu74/i18n/unicode and ./src/icu74/common/unicode to ./src/icu74/unicode (together)

4. Update ./LICENSE

5. Create ./src/icu74/LICENSE

7. Execute from ./src/icu74/:

    ```bash
    rm -f **/*.rc **/*.vcproj **/*.vcxproj **/*filters **/BUILD* **/Makefile.in
    mv i18n/sources.txt ../icu74_i18n_cpp.txt
    mv common/sources.txt ../icu74_common_cpp.txt
    mv stubdata/sources.txt ../icu74_stubdata_cpp.txt
    ```


# ICU data

Destination: ./src/icu74/data

```{bash}
for endian in l b; do
    wget -nc https://github.com/unicode-org/icu/releases/download/release-74-1/icu4c-74_1-data-bin-${endian}.zip
    unzip -o icu4c-74_1-data-bin-${endian}.zip
    sha256sum -b icudt74${endian}.dat > icudt74${endian}.dat.sha256sum
    xz -z -e -9 icudt74${endian}.dat
done
```

Only include icudt74l.dat.xz in the source bundle.
icudt74b.dat should be downloaded on demand during install.




## TODO: Patch ICU

! Use `#ifdef U_STRINGI_PATCHES`