#ifndef RENTAFACIL_H
#define RENTAFACIL_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QString>



namespace Ui {
class RentaFacil;
}

class RentaFacil : public QMainWindow
{
    Q_OBJECT

public:
    explicit RentaFacil(QWidget *parent = nullptr);
    ~RentaFacil();
    QString user;
    QString ruta1;
    QByteArray imagen1;

private slots:

    void on_btnRegToIni_clicked();

    void on_btnCreaCuenta_clicked();

    void on_btnRefIniSes_clicked();

    void on_btnback_clicked();

    void on_btnLoginRegistrate_clicked();

    void on_btnLogoutProp_clicked();

    void on_btnLogoutAdmin_clicked();

    void on_btnBackOffer_clicked();

    void on_btnNextOffer_clicked();

    void on_btnCancelaRegistro_2_clicked();

    void on_btnRegistrarCasa_clicked();

    void on_btnAgregaImg_clicked();

    void on_btnAddCasa_clicked();

    void on_radioButton_2_clicked();

    void on_btnContinuaReg_clicked();

    void on_radioClienteProp_clicked();

    void on_btnRegToIni_4_clicked();

    void on_btnRegToIni_3_clicked();

    void on_btnCrearCuentaPropietario_clicked();

    void on_btnRechazar_clicked();

    void on_btnAprobar_clicked();

    void on_btnRefReg_clicked();


    void on_pushButton_2_clicked();

    void on_comboBoxEstados_currentTextChanged(const QString &arg1);

    void on_solicitudesTableWidget_cellDoubleClicked(int row, int column);

    void on_btnback_Admin_clicked();

    void on_btnLogoutAdmin_5_clicked();

private:
    Ui::RentaFacil *ui;
    QSqlDatabase mDatabase;
    QString usuarioRegistro;
    QString tipoUsuarioRegistro;
    QString currentUsuario;
    QString idCasaG;

};

#endif // RENTAFACIL_H
