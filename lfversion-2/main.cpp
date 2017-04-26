#include "mainwindow.h"
#include "netaction.h"
#include "status.h"


//#include "netserver.h"
#include <QApplication>
#include <QDir>
#include<iostream>
#include <QDebug>
#include <cstdint>
#include <LWEEnc.h>
#include <BlissSig.h>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Status::init();
    MainWindow w;
    w.show();

    auto startServer = []{
       NetAction* server = new NetAction;
    };
    startServer();



    auto test = [](){
        uint16_t pubkey1[LWE_M],pubkey2[LWE_M], prikey[LWE_M];
        LWEKeyGen(pubkey1,pubkey2,prikey);
        for(int i=0; i<LWE_M;i++)
        {
            //qDebug()<<pubkey1[i]<<" ";
        }
        pubkey4io pk;
        seckey4io sk;
        BlissKeyGen(&pk,&sk);
        qDebug()<<"a2: "<<pk.a2;

       // pubkey4io pk; seckey4io sk;
        BlissKeyGen(&pk, &sk);

        string message = "Lorem ipsum dolor sit amet, consectetur adipiscing \
        elit. Nulla nec posuere mauris, eget facilisis nunc. Maecenas id libero at \
        tortor luctus volutpat. Nulla consequat tellus non ligula tincidunt, sed \
        tristique lectus volutpat. Curabitur vestibulum pretium blandit. Nunc nec \
        risus molestie urna elementum pellentesque. Nam id facilisis est, a \
        ultricies metus. Vestibulum sit amet nibh nec justo varius convallis id \
        nec justo. Maecenas id risus dignissim, volutpat nisi nec, fringilla elit. \
        Donec varius sem id risus sagittis, eu aliquam sem feugiat. Nulla non leo \
        tempus, pulvinar velit ut, euismod dui. Aliquam leo nunc, auctor et nulla \
        quis, dapibus vulputate quam. Morbi ut faucibus nisl, vitae vehicula elit. \
        Ut sed purus enim. Maecenas sit amet mi volutpat, rutrum velit quis, \
        volutpat quam. Vestibulum lacus tellus, placerat vitae magna vitae, \
        laoreet feugiat magna. Aliquam nulla lacus, scelerisque eu mauris a, \
        viverra suscipit ligula.";
        signature4io sig;
        BlissSigM(&pk, &sk, &sig, message);
        cout<< BlissVerifyM(&pk, &sig, message) << endl;

        cout<< "------------------------------" << endl;

      //  BlissSigF(&pk, &sk, &sig, "test_file1.txt");
        //cout<< BlissVerifyF(&pk, &sig, "test_file1.txt") << endl;

        cout<< "------------------------------" << endl;

      //  BlissSigF(&pk, &sk, &sig, "test_file1.txt");
        //cout<< BlissVerifyF(&pk, &sig, "test_file2.txt") << endl;

    };
    return a.exec();
}






