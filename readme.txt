1. Instalação
sudo apt-get update 
sudo apt-get -y install postgreql-14 postgresql-14-pldebugger postgresql-client-14 postgresql-common postgresql-server-dev-14 
sudo apt-get -y install postgresql-14-postgis-3-scripts=3.2.0+dfsg-1ubuntu1 postgresql-14-postgis-3=3.2.0+dfsg-1ubuntu1 
sudo apt-get -y install build-essential cmake libproj-dev libjson-c-dev

2. Compilação
git clone git@github.com:ffeller/MasterMobilityDB.git
cd MasterMobilityDB
sudo make install
cd MobilityDB
unzip MobilityDB-1.0.zip
mkdir -p MobilityDB-1.0/build
cd MoblityDB-1.0/build 
cmake ..
make
sudo make install

3. Registro das extensões
sudo su - postgres
createdb -e -T template0 mobility
psql -e -d mobility -c "create extension if not exists mastermobilitydb cascade"
