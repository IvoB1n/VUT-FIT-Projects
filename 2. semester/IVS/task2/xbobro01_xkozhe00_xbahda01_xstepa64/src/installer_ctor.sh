#! /bin/sh
cd ..
path=$(pwd)
check_path="install/trelico_calculator_v_1.2/usr/share/"
deb="install/trelico_calculator_v_1.2"
cd $check_path
if [ -d "trelico_calc" ]
then
        rm -rf trelico_calc
fi

mkdir trelico_calc
mkdir trelico_calc/src
chmod 775 trelico_calc
chmod 775 trelico_calc/src

cd ..
cd ..
cd ..
echo "$(pwd)"
if [ -f "trelico_calculator_v_1.2.deb" ]
then
        rm "trelico_calculator_v_1.2.deb"
        echo "deleting .deb file"
fi

cd $path

cp src/main.py ""$check_path"trelico_calc/src"
cp src/mathlib.py ""$check_path"trelico_calc/src"
cp -r src/gui ""$check_path"trelico_calc/src"
cp src/calculator.py ""$check_path"trelico_calc/src"
cp dokumentace.pdf ""$check_path"trelico_calc"


echo "Folder $check_path""trelico_calc was created successfully!"
dpkg-deb --build "$deb"

cd src
