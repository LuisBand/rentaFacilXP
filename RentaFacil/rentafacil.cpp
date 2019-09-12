#include "rentafacil.h"
#include "ui_rentafacil.h"
#include "registro.h"
#include<QString>
#include <QSqlQuery>
#include<QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QPixmap>
#include <QCompleter>
#include <QFileSystemModel>
//Este es mi comentario de prueba

RentaFacil::RentaFacil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RentaFacil)
{
    ui->setupUi(this);

    //Base De Datos:
    //Base De Datos:
    QSqlDatabase db;
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("rentaFacil");
    db.setUserName("root");
    db.setPassword("luisdrew1394");

    if(!db.open()){
        qDebug()<<"Error ";
    }
    else{
          qDebug()<<"Conectada ";
    }

    QSqlQuery catalogo;
    QString catalogosql;
    QString titulo;

    catalogosql = "select titulo from Casa";
    catalogo.exec(catalogosql);

    int counterf = 0;
    int counterc = 0;

    while (catalogo.next()) {
        titulo = catalogo.value(0).toString();

        QPushButton *h = new QPushButton("Soy una casa");
        ui->layout->addWidget(h , counterf, counterc, 1, 1);
        h->setFixedSize(203, 100);
        QLabel *label = new QLabel;
        label->setText(titulo);
        label->setFixedSize(203, 20);
        ui->layout->addWidget(label, counterf + 1, counterc, 1, 1);
        counterc++;

        if (counterc == 3){
            counterf= counterf + 2;
            counterc = 0;
        }
    }


    QSqlQuery estados1;
    QString buscar;
    buscar="select *from Estado";
    estados1.prepare(buscar);
    estados1.exec();
    while(estados1.next())
    {
        ui->comboBoxEstados->addItem(estados1.value(2).toString());
    }

    ui->lineCP->setValidator(new QIntValidator(this));
    ui->lineNoBanos->setValidator(new QIntValidator(this));
    ui->lineNoCuartos->setValidator(new QIntValidator(this));
    ui->lineNoPersonas->setValidator(new QIntValidator(this));
    ui->lineTarifaDiaria->setValidator(new QIntValidator(this));
    ui->lineTarifaSemanal->setValidator(new QIntValidator(this));
    ui->registroTel->setValidator(new QIntValidator(this));
    ui->registroNom_4->setValidator(new QDoubleValidator(this));
    ui->registroApM_4->setValidator(new QIntValidator(this));
    ui->stackedWidget->setCurrentIndex(0);
}

RentaFacil::~RentaFacil()
{
    delete ui;
}
void clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void RentaFacil::on_btnCreaCuenta_clicked()
{
    QString nombre = ui->registroNom->text();
    QString aPaterno = ui->registroApP->text();
    QString aMaterno = ui->registroApM->text();
    QString telefono = ui->registroTel->text();
    QString usuario = ui->registroUsuario->text();
    QString contra = ui->registroPass->text();
    QString nacimiento = ui->dateEdit_2->text();

    usuarioRegistro = usuario;

    qDebug()<<usuarioRegistro;



    int date = (ui->dateEdit_2->date().currentDate().year())-ui->dateEdit_2->date().year();


    QSqlQuery query;
    QSqlQuery query2;
    QString sql;
    QString sql2;


    if(nombre == "" || aPaterno == "" || aMaterno == "" || telefono == "" || usuario == "" || contra == "" || nacimiento == ""){
        QMessageBox messageBox(QMessageBox::Warning,
                                 tr("Critical Error"), tr("Por favor, llene todos los campos."), QMessageBox::Yes);

         messageBox.setButtonText(QMessageBox::Yes, tr("Entiendo"));

         if (messageBox.exec() == QMessageBox::Yes){

          }

    }else {
        if(ui->radioButton->isChecked()==true){
            tipoUsuarioRegistro = "Cliente";
            if( date >= 18){
                sql = "select nombreUsuario from cliente where nombreUsuario = '"+usuario+"';";
                int contador = 0;
                query.exec(sql);

                while (query.next()) {
                    contador++;
                }

                if(contador > 0){
                    QMessageBox messageBox(QMessageBox::Warning,
                                             tr("Critical Error"), tr("Este usuario ya existe"), QMessageBox::Yes);

                     messageBox.setButtonText(QMessageBox::Yes, tr("Entiendo"));

                     if (messageBox.exec() == QMessageBox::Yes){

                      }
                }
                else if(contador ==  0) {
                    sql = "insert into cliente(nombre, aPaterno, aMaterno, telefono, fNacimiento, nombreUsuario, clave) values ("
                          "'"+nombre+"', '"+aPaterno+"', '"+aMaterno+"', '"+telefono+"', '"+nacimiento+"', '"+usuario+"', '"+contra+"');";

                     query.exec(sql);
                    ui->stackedWidget->setCurrentIndex(4);
                 }
            }

            else {

                QMessageBox messageBox(QMessageBox::Warning,
                                         tr("Critical Error"), tr("Eres menor de edad"), QMessageBox::Yes);

                 messageBox.setButtonText(QMessageBox::Yes, tr("Entiendo"));

                 if (messageBox.exec() == QMessageBox::Yes){
                         ui->registroNom->setText("");
                         ui->registroApP->setText("");
                         ui->registroApM->setText("");
                         ui->registroTel->setText("");
                         ui->registroUsuario->setText("");
                         ui->registroPass->setText("");
                  }

            }


        }
        else if (ui->radioButton_2->isChecked()==true) {
            tipoUsuarioRegistro = "Propietario";
            if( date >= 18){
                sql = "select nombreUsuario from propietario where nombreUsuario = '"+usuario+"';";
                int contador = 0;
                query.exec(sql);

                while (query.next()) {
                    contador++;
                }

                if(contador > 0){
                    QMessageBox messageBox(QMessageBox::Warning,
                                             tr("Critical Error"), tr("Este usuario ya existe"), QMessageBox::Yes);

                     messageBox.setButtonText(QMessageBox::Yes, tr("Entiendo"));

                     if (messageBox.exec() == QMessageBox::Yes){

                      }
                }
                else if(contador ==  0) {
                    qDebug()<<"lleguéeeeeeeee";
                    sql = "insert into propietario(nombre, aPaterno, aMaterno, telefono, fNacimiento, nombreUsuario, clave) values ("
                          "'"+nombre+"', '"+aPaterno+"', '"+aMaterno+"', '"+telefono+"', '"+nacimiento+"', '"+usuario+"', '"+contra+"');";

                    qDebug()<<sql;
                    query.exec(sql);
                    ui->stackedWidget->setCurrentIndex(4);
                 }
            }

            else {

                QMessageBox messageBox(QMessageBox::Warning,
                                         tr("Critical Error"), tr("Eres menor de edad"), QMessageBox::Yes);

                 messageBox.setButtonText(QMessageBox::Yes, tr("Entiendo"));

                 if (messageBox.exec() == QMessageBox::Yes){
                         ui->registroNom->setText("");
                         ui->registroApP->setText("");
                         ui->registroApM->setText("");
                         ui->registroTel->setText("");
                         ui->registroUsuario->setText("");
                         ui->registroPass->setText("");
                  }

            }


        }
        else {
            QMessageBox messageBox(QMessageBox::Warning,
                                     tr("Critical Error"), tr("Por favor selecciona un tipo de usuario"), QMessageBox::Yes);

             messageBox.setButtonText(QMessageBox::Yes, tr("Entiendo"));

             if (messageBox.exec() == QMessageBox::Yes){

              }
        }

     qDebug()<<tipoUsuarioRegistro;
     qDebug()<<usuarioRegistro;


    }






}

void RentaFacil::on_btnRefIniSes_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void RentaFacil::on_btnback_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void RentaFacil::on_btnLoginRegistrate_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void RentaFacil::on_btnLogoutAdmin_clicked()
{
    int numeroColumnas = ui->solicitudesTableWidget->rowCount();
                    QList<int> numeros;
                    for(int i=1; i<=numeroColumnas; i++){
                      numeros.append(i);
                      ui->solicitudesTableWidget->removeRow(numeros.value(i));
                    }

    ui->stackedWidget->setCurrentIndex(0);
}

/*---- Ofertar Casa ----*/
void RentaFacil::on_btnNextOffer_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void RentaFacil::on_btnBackOffer_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void RentaFacil::on_btnRegistrarCasa_clicked()
{
    QString titulo=ui->lineTitulo->text();
    QString ubicacion=ui->lineUbicacion->text();
    QString cp=ui->lineCP->text();
    QString estado=ui->comboBoxEstados->currentText();
    QString municipio=ui->comboBoxMunicipios->currentText();
    QString banios=ui->lineNoBanos->text();
    QString diario=ui->lineTarifaDiaria->text();
    QString semana=ui->lineTarifaSemanal->text();
    QString personas=ui->lineNoPersonas->text();
    QString cuartos=ui->lineNoCuartos->text();
    QString sianimal="1";
    QString noanimal="0";
    QString descripcion=ui->textEdit->toPlainText();



    QString Buscarmuni;
    Buscarmuni="select *from Municipio where nombre='"+municipio+"' ";
    QSqlQuery idbus;
    idbus.prepare(Buscarmuni);
    idbus.exec();
    idbus.next();
    QString idmun=idbus.value(0).toString();

    QString insertdir;
    insertdir="insert into Direccion(domicilio,cp,idMunicipio)values('"+ubicacion+"','"+cp+"','"+idmun+"');  ";
    QSqlQuery insert1;
    insert1.prepare(insertdir);
    insert1.exec();



    if(ui->radioSi_4->isChecked())
    {
        QString idd;

        //aqui busco el id de la direccion
        QString iddir;
        iddir="select id from Direccion where domicilio='"+ubicacion+"'  ;  ";
        QSqlQuery insert2;
        insert2.prepare(iddir);
        insert2.exec();

        while ( insert2.next()){
        idd=insert2.value(0).toString();
        qDebug()<<idd;
        }


        QString insertcasa;
        insertcasa="insert into Casa(numeroCuartos,numeroBanios,numeroPersonas,animales,descripcion,titulo,tarifaSemanal,tarifaDiaria,statusc,idDireccion,nUsuarioP)"
                    " values("+cuartos+","+banios+" ,"+personas+" ,"+sianimal+" ,'"+descripcion+"' ,'"+titulo+"' ,'"+semana+"' ,'"+diario+"' ,'0' ,'"+idd+"','"+user+"' ); " ;

         qDebug()<<insertcasa;
        QSqlQuery insertcasa1;
        insertcasa1.prepare(insertcasa);
        insertcasa1.exec();

        QString idcasa;
        idcasa="select *from Casa where titulo='"+titulo+"' and nUsuarioP='"+user+"' ; ";
        QSqlQuery idbuscasa;
        idbuscasa.prepare(idcasa);
        idbuscasa.exec();
        idbuscasa.next();

        QString idCasa1=idbuscasa.value(0).toString();
        qDebug()<<idCasa1;

        QString insertfoto;
        insertfoto="insert into fotocasa(ruta,idCasa,datosf)values('"+ruta1+"','"+idCasa1+"',:datos);   ";
        QSqlQuery insertfoto1;
        insertfoto1.prepare(insertfoto);
        insertfoto1.bindValue(":datos",imagen1);
        insertfoto1.exec();


    }
    else if(ui->radioNo_4->isChecked())
    {
        //aqui busco el id de la direccion
        QString iddir;
        iddir="select *from Direccion where domicilio='"+ubicacion+"'  ;  ";
        QSqlQuery insert2;
        insert2.prepare(iddir);
        insert2.exec();
        insert2.next();
        QString idd=insert2.value(0).toByteArray().constData();
        qDebug()<<idd;

        QString insertcasa;
        insertcasa="insert into Casa(numeroCuartos,numeroBanios,numeroPersonas,animales,descripcion,titulo,tarifaSemanal,tarifaDiaria,statusc,idDireccion,nUsuarioP)"
                    " values('"+cuartos+"','"+banios+"' ,'"+personas+"' ,'"+noanimal+"' ,'"+descripcion+"' ,'"+titulo+"' ,'"+semana+"' ,'"+diario+"' ,'0' ,'"+idd+"','"+user+"' ); " ;

         qDebug()<<insertcasa;
        QSqlQuery insertcasa1;
        insertcasa1.prepare(insertcasa);
        insertcasa1.exec();

        QString idcasa;
        idcasa="select *from Casa where titulo='"+titulo+"' and nUsuarioP='"+user+"' ; ";
        QSqlQuery idbuscasa;
        idbuscasa.prepare(idcasa);
        idbuscasa.exec();
        idbuscasa.next();

        QString idCasa1=idbuscasa.value(0).toString();
        qDebug()<<idCasa1;

        QString insertfoto;
        insertfoto="insert into fotocasa(ruta,idCasa,datosf)values('"+ruta1+"','"+idCasa1+"',:datos);   ";
        QSqlQuery insertfoto1;
        insertfoto1.prepare(insertfoto);
        insertfoto1.bindValue(":datos",imagen1);
        insertfoto1.exec();
        QMessageBox informacion;
        informacion.setWindowTitle("solicitud enviada");
        informacion.setText ("tu solicitud de guardo y envio correctamente");
        informacion.setStandardButtons( QMessageBox::Ok) ;
        informacion.setDefaultButton (QMessageBox ::Ok ) ;
        informacion.setButtonText( QMessageBox::Ok,"Aceptar");
        informacion.exec();

    }
    else
    {
        QMessageBox messageBox(QMessageBox::Warning,
                                 tr("Critical Error"), tr("selecciona el acceso a nimales"), QMessageBox::Yes);

         messageBox.setButtonText(QMessageBox::Yes, tr("Entiendo"));

         if (messageBox.exec() == QMessageBox::Yes){

          }
    }





ui->stackedWidget->setCurrentIndex(5);




}


//agregar imagen
void RentaFacil::on_btnAgregaImg_clicked()
{
 auto nombreArchivo = QFileDialog::getOpenFileName(this,"abrir imagen",QDir::rootPath(),"imagenes(*.png *.jpg *.jpeg);; cualquier archivo(*.*)");
 QString ruta=nombreArchivo;
 QFile archivo(ruta);
 if(!archivo.open(QIODevice::ReadOnly))
 {
     return;
 }
 QByteArray mostrar=archivo.readAll();
 QPixmap imag;
 imag.loadFromData(mostrar);
 ui->lblFoto_3->setPixmap(imag);

 ruta1=ruta;
 imagen1=mostrar;



}

/*---- Propietario ----*/
void RentaFacil::on_btnAddCasa_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void RentaFacil::on_btnLogoutProp_clicked()
{

   clearLayout(ui->misCasasLayout);
   ui->stackedWidget->setCurrentIndex(0);
}
//registro de casa cancelado
void RentaFacil::on_btnCancelaRegistro_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


/*---------------------*/

/*---- Registro Cuenta----*/
    void RentaFacil::on_radioButton_2_clicked()
    {
        ui->radioButton_2->setEnabled(true);
    }

    //Pasa a ventana de cuenta bancaria
    void RentaFacil::on_btnContinuaReg_clicked()
    {
        ui->stackedWidget->setCurrentIndex(4);
    }

    void RentaFacil::on_radioClienteProp_clicked()
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    // ---- registro a iniciar sesión ----
        void RentaFacil::on_btnRegToIni_clicked()
        {
            ui->stackedWidget->setCurrentIndex(1);
        }

        void RentaFacil::on_btnRegToIni_3_clicked()
        {
            ui->stackedWidget->setCurrentIndex(1);
        }

        void RentaFacil::on_btnRegToIni_4_clicked()
        {
            ui->stackedWidget->setCurrentIndex(1);
        }

    // -----------------------------------

void RentaFacil::on_btnCrearCuentaPropietario_clicked()
{
    QString numero = ui->registroNom_4->text();
    QString expira = ui->dateEdit_3->text();
    QString codigo = ui->registroApM_4->text();
    QString banco = ui->comboBox_2->currentText();

    QSqlQuery query;
    QString sql;

    if(numero == "" || expira == "" || codigo == "" || banco == ""){
        QMessageBox messageBox(QMessageBox::Warning,
                                 tr("Critical Error"), tr("Algunos campod no han sido llenados aun."), QMessageBox::Yes);

         messageBox.setButtonText(QMessageBox::Yes, tr("Entiendo"));

         if (messageBox.exec() == QMessageBox::Yes){

          }
    }else {
        if(tipoUsuarioRegistro == "Cliente"){
            sql = "insert into cBancariaC (numero, fVencimiento, saldo, codigo, banco, idCliente) values ("
                  +numero+", '"+expira+"', 1000000, "+codigo+", '"+banco+"', '"+usuarioRegistro+"');";

            query.exec(sql);

            QMessageBox informacion;
            informacion.setWindowTitle("Usuario creado correctamente");
            informacion.setText ("tus datos se guardaron correctamente");
            informacion.setStandardButtons( QMessageBox::Ok) ;
            informacion.setDefaultButton (QMessageBox ::Ok ) ;
            informacion.setButtonText( QMessageBox::Ok,"Aceptar");
            informacion.exec();

            ui->stackedWidget->setCurrentIndex(0);

        }
        else if (tipoUsuarioRegistro == "Propietario") {
            sql = "insert into cBancariaP (numero, fVencimiento, saldo, codigo, banco, idPropietario) values ("
                  +numero+", '"+expira+"', 0, "+codigo+", '"+banco+"', '"+usuarioRegistro+"');";

            qDebug()<<sql;
            query.exec(sql);

            QMessageBox informacion;
            informacion.setWindowTitle("Usuario creado correctamente");
            informacion.setText ("tus datos se guardaron correctamente");
            informacion.setStandardButtons( QMessageBox::Ok) ;
            informacion.setDefaultButton (QMessageBox ::Ok ) ;
            informacion.setButtonText( QMessageBox::Ok,"Aceptar");
            informacion.exec();

            ui->stackedWidget->setCurrentIndex(0);
        }
    }


    ui->registroNom->clear();
    ui->registroApM->clear();
    ui->registroApP->clear();
    ui->registroTel->clear();
    ui->registroUsuario->clear();
    ui->registroPass->clear();
    ui->registroNom_4->clear();
    ui->registroApM_4->clear();
    ui->dateEdit->clear();
    ui->comboBox_2->clear();
    ui->dateEdit_3->clear();
}

/*------------------*/

//Administrador rechaza la solicitud de la casa
void RentaFacil::on_btnRechazar_clicked()
{
    QSqlQuery query;
    QString sql;
    QString calificacion = ui->comboBox->currentText();
    QString idCas;
    sql = "delete from fotocasa where idCasa = "+idCasaG+";";
    query.exec(sql);
    sql = "delete from casa where id = "+idCasaG+";";
    query.exec(sql);
    sql = "select idDireccion from casa where id = "+idCasaG+";";
    query.exec(sql);
    while (query.next()) {
        idCas = query.value(0).toString();
    }
    sql = "delete from direccion where id = "+idCas+";";
    query.exec(sql);

    int numeroColumnas = ui->solicitudesTableWidget->rowCount();
                    QList<int> numeros;
                    for(int i=1; i<=numeroColumnas; i++){
                      numeros.append(i);
                      ui->solicitudesTableWidget->removeRow(numeros.value(i));
                    }

    sql = "select * from solicitudes;";
    query.exec(sql);

    while(query.next()){
        QString propietario = query.value(0).toString();
        QString titulo = query.value(1).toString();
        QString estado = query.value(2).toString();
        QString municipio = query.value(3).toString();
        QString direccion = query.value(4).toString();

        ui->solicitudesTableWidget->insertRow(ui->solicitudesTableWidget->rowCount());
                int fila=ui->solicitudesTableWidget->rowCount()-1;

                ui->solicitudesTableWidget->setItem(fila, 0, new QTableWidgetItem(propietario));
                ui->solicitudesTableWidget->setItem(fila, 1, new QTableWidgetItem(titulo));
                ui->solicitudesTableWidget->setItem(fila, 2, new QTableWidgetItem(estado));
                ui->solicitudesTableWidget->setItem(fila, 3, new QTableWidgetItem(municipio));
                ui->solicitudesTableWidget->setItem(fila, 4, new QTableWidgetItem(direccion));

    }

    ui->stackedWidget->setCurrentIndex(8);
}
//Administrador acepta solicitud de la casa
void RentaFacil::on_btnAprobar_clicked()
{
    QSqlQuery query;
    QString sql;
    QString calificacion = ui->comboBox->currentText();
    sql = "update casa set statusc = 1, calificacion = "+calificacion+" where id = "+idCasaG+";";
    query.exec(sql);

    int numeroColumnas = ui->solicitudesTableWidget->rowCount();
                    QList<int> numeros;
                    for(int i=1; i<=numeroColumnas; i++){
                      numeros.append(i);
                      ui->solicitudesTableWidget->removeRow(numeros.value(i));
                    }

    sql = "select * from solicitudes;";
    query.exec(sql);

    while(query.next()){
        QString propietario = query.value(0).toString();
        QString titulo = query.value(1).toString();
        QString estado = query.value(2).toString();
        QString municipio = query.value(3).toString();
        QString direccion = query.value(4).toString();

        ui->solicitudesTableWidget->insertRow(ui->solicitudesTableWidget->rowCount());
                int fila=ui->solicitudesTableWidget->rowCount()-1;

                ui->solicitudesTableWidget->setItem(fila, 0, new QTableWidgetItem(propietario));
                ui->solicitudesTableWidget->setItem(fila, 1, new QTableWidgetItem(titulo));
                ui->solicitudesTableWidget->setItem(fila, 2, new QTableWidgetItem(estado));
                ui->solicitudesTableWidget->setItem(fila, 3, new QTableWidgetItem(municipio));
                ui->solicitudesTableWidget->setItem(fila, 4, new QTableWidgetItem(direccion));

    }



    ui->stackedWidget->setCurrentIndex(8);
}

void RentaFacil::on_btnRefReg_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void RentaFacil::on_pushButton_2_clicked()
{
    currentUsuario = ui->loginNom->text();
    QString usuario = ui->loginNom->text();
    QString clave = ui->loginPass->text();

    QString clavev;
    QSqlQuery query;
    QString sql;

    int contador = 0;
    if(ui->iniciarClienteRB->isChecked() == true){
        sql = "select clave from cliente where nombreUsuario = '"+usuario+"';";
        query.exec(sql);

        while (query.next()) {
            contador++;
            clavev = query.value(0).toString();
        }

        if(contador == 0){
            QMessageBox informacion;
            informacion.setWindowTitle("No existe el usuario");
            informacion.setText ("El usuario ingresado no ha sido registrado");
            informacion.setStandardButtons( QMessageBox::Ok) ;
            informacion.setDefaultButton (QMessageBox ::Ok ) ;
            informacion.setButtonText( QMessageBox::Ok,"Aceptar");
            informacion.exec();
        }
        else if (contador == 1) {
            if(clave == clavev){
                ui->stackedWidget->setCurrentIndex(10);
                user=ui->loginNom->text();
            }
            else {
                QMessageBox informacion;
                informacion.setWindowTitle("Contraseña incorrecta");
                informacion.setText ("La contraseña es incorrecta");
                informacion.setStandardButtons( QMessageBox::Ok) ;
                informacion.setDefaultButton (QMessageBox ::Ok ) ;
                informacion.setButtonText( QMessageBox::Ok,"Aceptar");
                informacion.exec();
            }
        }



    }
    else if (ui->iniciarPropietarioRB->isChecked() == true) {
        QSqlQuery catalogo;
        QString catalogosql;
        QString titulo;
        int statusc;
        catalogosql = "select titulo, statusc from Casa where nUsuarioP = '"+currentUsuario+"';";
        catalogo.exec(catalogosql);
        qDebug() << catalogosql;

        int counterf = 0;
        int counterc = 0;
        while (catalogo.next()) {
            titulo = catalogo.value(0).toString();
            statusc = catalogo.value(1).toInt();

            if(statusc == 0){
                QPushButton *h = new QPushButton("Soy una casa");
                ui->misCasasLayout->addWidget(h , counterf, counterc, 1, 1);
                h->setFixedSize(203, 100);
                h->setEnabled(false);
                QLabel *label = new QLabel;
                label->setText(titulo);
                label->setFixedSize(203, 20);
                ui->misCasasLayout->addWidget(label, counterf + 1, counterc, 1, 1);
                counterc++;

            }else if (statusc == 1) {
                QPushButton *h = new QPushButton("Soy una casa");
                ui->misCasasLayout->addWidget(h , counterf, counterc, 1, 1);
                h->setFixedSize(203, 100);
                QLabel *label = new QLabel;
                label->setText(titulo);
                label->setFixedSize(203, 20);
                ui->misCasasLayout->addWidget(label, counterf + 1, counterc, 1, 1);
                counterc++;
            }


            if (counterc == 3){
                counterf= counterf + 2;
                counterc = 0;
            }
        }

        sql = "select clave from propietario where nombreUsuario = '"+usuario+"';";
        query.exec(sql);

        while (query.next()) {
            contador++;
            clavev = query.value(0).toString();
        }

        if(contador == 0){
            QMessageBox informacion;
            informacion.setWindowTitle("No existe el usuario");
            informacion.setText ("El usuario ingresado no ha sido registrado");
            informacion.setStandardButtons( QMessageBox::Ok) ;
            informacion.setDefaultButton (QMessageBox ::Ok ) ;
            informacion.setButtonText( QMessageBox::Ok,"Aceptar");
            informacion.exec();
        }
        else if (contador == 1) {
            if(clave == clavev){
                ui->stackedWidget->setCurrentIndex(5);
                user=usuario;
            }
            else {
                QMessageBox informacion;
                informacion.setWindowTitle("Contraseña incorrecta");
                informacion.setText ("La contraseña es incorrecta");
                informacion.setStandardButtons( QMessageBox::Ok) ;
                informacion.setDefaultButton (QMessageBox ::Ok ) ;
                informacion.setButtonText( QMessageBox::Ok,"Aceptar");
                informacion.exec();
            }
        }

    }else if (ui->iniciarAdministradorRB->isChecked() == true) {

        if(usuario == "Admin" && clave == "admin1234"){
        sql = "select * from solicitudes;";
        query.exec(sql);

        while(query.next()){
            QString propietario = query.value(0).toString();
            QString titulo = query.value(1).toString();
            QString estado = query.value(2).toString();
            QString municipio = query.value(3).toString();
            QString direccion = query.value(4).toString();

            ui->solicitudesTableWidget->insertRow(ui->solicitudesTableWidget->rowCount());
                    int fila=ui->solicitudesTableWidget->rowCount()-1;

                    ui->solicitudesTableWidget->setItem(fila, 0, new QTableWidgetItem(propietario));
                    ui->solicitudesTableWidget->setItem(fila, 1, new QTableWidgetItem(titulo));
                    ui->solicitudesTableWidget->setItem(fila, 2, new QTableWidgetItem(estado));
                    ui->solicitudesTableWidget->setItem(fila, 3, new QTableWidgetItem(municipio));
                    ui->solicitudesTableWidget->setItem(fila, 4, new QTableWidgetItem(direccion));
        }
            ui->stackedWidget->setCurrentIndex(8);
        }
        else {
            QMessageBox informacion;
            informacion.setWindowTitle("Contraseña o Usuario incorrectos");
            informacion.setText ("Contraseña o Usuario incorrectos");
            informacion.setStandardButtons( QMessageBox::Ok) ;
            informacion.setDefaultButton (QMessageBox ::Ok ) ;
            informacion.setButtonText( QMessageBox::Ok,"Aceptar");
            informacion.exec();
        }
    }
}

void RentaFacil::on_comboBoxEstados_currentTextChanged(const QString &arg1)
{
    ui->comboBoxMunicipios->clear();
    QString municipio=ui->comboBoxEstados->currentText();
       QSqlQuery buscaEs;
       QString idEstado;
       idEstado="select id from Estado where nombre='"+municipio+"'  ";
       buscaEs.prepare(idEstado);
       buscaEs.exec();
       buscaEs.next();
       QString Estado1=buscaEs.value(0).toString();
       QString nombreEs;
       nombreEs="select *from Municipio where estado_id='"+Estado1+"' ";
       QSqlQuery nuevo;
       nuevo.prepare(nombreEs);
       nuevo.exec();

       while(nuevo.next())
       {
           ui->comboBoxMunicipios->addItem(nuevo.value(3).toString());
       }
}

void RentaFacil::on_solicitudesTableWidget_cellDoubleClicked(int row, int column)
{

    QString usuario  = ui->solicitudesTableWidget->item(row,0)->text();
    QString titulo = ui->solicitudesTableWidget->item(row, 1)->text();

    QString numeroPersonas, numeroCuartos, numeroBanios, animales, tarifaD, tarifaS, descripcion, domicilio, cp, estado, municipio;
    QByteArray foto;


    QSqlQuery query;
    QString sql;

    QPixmap pixmap;
    sql = "call informacion ('"+usuario+"', '"+titulo+"');";
    query.exec(sql);

    while(query.next()){
        numeroPersonas = query.value(2).toString();
        numeroCuartos = query.value(3).toString();
        numeroBanios = query.value(4).toString();
        animales = query.value(5).toString();
        tarifaD = query.value(6).toString();
        tarifaS = query.value(7).toString();
        descripcion = query.value(8).toString();
        estado = query.value(9).toString();
        municipio = query.value(10).toString();
        domicilio = query.value(11).toString();
        cp = query.value(12).toString();
        foto = query.value(13).toByteArray();
    }

    pixmap.loadFromData(foto);



    ui->lblTituloPropiedad->setText(titulo);
    ui->lblPersonasAdmitidas->setText(numeroPersonas);
    ui->lblNumCuartos->setText(numeroCuartos);
    ui->lblBanios->setText(numeroBanios);
    ui->lblAnimales->setText(animales);
    ui->lblTarifaDia->setText(tarifaD);
    ui->lblTarifaSem->setText(tarifaS);
    ui->PTDescripcion->setPlainText(descripcion);
    ui->lblDireccion->setText(domicilio);
    ui->lblCP->setText(cp);
    ui->lblEstado->setText(estado);
    ui->lblMunicipio->setText(municipio);
    ui->lblFoto_2->setPixmap(pixmap);


    sql = "select id from casa where titulo = '"+titulo+"' and nUsuarioP = '"+usuario+"';";
    query.exec(sql);
    while(query.next()){
        idCasaG = query.value(0).toString();
    }

    ui->stackedWidget->setCurrentIndex(9);
}

void RentaFacil::on_btnback_Admin_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void RentaFacil::on_btnLogoutAdmin_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
