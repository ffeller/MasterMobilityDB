1. Compilação
git clone git@github.com:ffeller/MasterMobilityDB.git
sudo make install
cd MobilityDB/build
sudo make install

2. Instalação
sudo apt-get update 
sudo apt-get -y install postgreql-14 postgresql-14-pldebugger postgresql-client-14 postgresql-common postgresql-server-dev-14 
sudo apt-get -y install postgresql-14-postgis-3-scripts=3.2.0+dfsg-1ubuntu1 postgresql-14-postgis-3=3.2.0+dfsg-1ubuntu1 

3. Registro das extensões
sudo su - postgres
psql -e -d <<EOF 
create schema if not exists master; 
create extensiom if not exists postgis; 
create extension if not exists file_fdw; 
create extension if not exists mobilitydb; 
create extension if not exists mastermobilitydb; 
EOF

4. Teste
select master.aspect_count();
aspect_count
0

