/**
 *           _           _             _     _
 *     /\  /(_)_ __ ___ | | _____  ___| |__ (_)
 *    / /_/ / | '__/ _ \| |/ / _ \/ __| '_ \| |
 *   / __  /| | | | (_) |   < (_) \__ \ | | | |
 *   \/ /_/ |_|_|  \___/|_|\_\___/|___/_| |_|_|
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *  clGenerator est un générateur de classes/sources C++
 *  Author: Elyas Kamel
 *  Contact: hirokoshi@gw2.fr OR melyasfa@gmail.com
 */

#include "ResultWindow.h"

ResultWindow::ResultWindow(QString &codeClass, QString &codeCpp, QString& nameClass, QWidget *parent) : QDialog(parent), m_codeClass(codeClass), m_codeCpp(codeCpp), m_nameClass(nameClass)
{
    /**
     * @ - Création des widgets
     **/

    //Tabs
    m_tab = new QTabWidget;

    //Pages
    m_pageCpp = new QWidget;
    m_pageH = new QWidget;

    //Contenu de la page H
    m_textCode = new QTextEdit();
    m_textCode->setPlainText(m_codeClass);
    m_textCode->setReadOnly(true);
    m_textCode->setFont(QFont("Courier New"));
    m_textCode->setLineWrapMode(QTextEdit::NoWrap);

    QVBoxLayout *lone = new QVBoxLayout;
    lone->addWidget(m_textCode);

    m_pageH->setLayout(lone);


    //Contenu de la page Cpp
    m_textCpp = new QTextEdit();
    m_textCpp->setPlainText(m_codeCpp);
    m_textCpp->setReadOnly(true);
    m_textCpp->setFont(QFont("Courier New"));
    m_textCpp->setLineWrapMode(QTextEdit::NoWrap);

    QVBoxLayout *ltwo = new QVBoxLayout;
    ltwo->addWidget(m_textCpp);

    m_pageCpp->setLayout(ltwo);

    //Création des onglets
    m_tab->addTab(m_pageH, m_nameClass + ".h");
    m_tab->addTab(m_pageCpp, m_nameClass + ".cpp");

    m_closeButton = new QPushButton("Fermer");
    m_saveButton = new QPushButton("Enregistrer");

    QHBoxLayout *m_buttonsLayout = new QHBoxLayout;
    m_buttonsLayout->addWidget(m_saveButton);
    m_buttonsLayout->addWidget(m_closeButton);

    m_principalLayout = new QVBoxLayout;
    m_principalLayout->addWidget(m_tab);
    m_principalLayout->addLayout(m_buttonsLayout);

    /**
     * @ - Connexions
     **/
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(saveFiles()));

    setLayout(m_principalLayout);

    setWindowTitle("clGenerator - Résultat");
    resize(350, 450);
}

void ResultWindow::saveFiles() {
    QString headerName = QFileDialog::getSaveFileName(this, "Enregistrer un fichier header", QString(m_nameClass), "Fichier header C++ (*.h *.hpp)");
    QString sourceName = QFileDialog::getSaveFileName(this, "Enregistrer un fichier source", QString(m_nameClass), "Fichier source C++ (*.cpp)");

    if(!headerName.isEmpty() && !sourceName.isEmpty()) {
        QFile fileHeader(headerName), fileSource(sourceName);
        fileHeader.open(QIODevice::WriteOnly | QIODevice::Text);
        fileSource.open(QIODevice::WriteOnly | QIODevice::Text);

        QTextStream out(&fileHeader);
        QTextStream outTwo(&fileSource);
        out << m_codeClass;
        outTwo << m_codeCpp;

        fileHeader.close();
        fileSource.close();
    } else {
        QMessageBox::critical(this, "Erreur", "Il y a eu une erreur lors de l'enregistrement des fichiers.");
    }
}
