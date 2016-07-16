
cd $HOME/Pulpit/proj/rcn3d/

file_name=${1%.*}
echo $file_name

make -B "$file_name"
