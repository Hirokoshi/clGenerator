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

#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H
#include <QtGui>

class ResultWindow : public QDialog {

    Q_OBJECT

    public:
        /**
         * @brief créé une fenêtre de dialogue contenant le code de la classe
         * @param codeClass => le code généré
         */
        ResultWindow(QString &codeClass, QString &codeCpp, QString& nameClass, QWidget *parent = 0);

    public slots:
        /**
         * @brief saveFiles => permet de sauvegarder les fichiers .cpp et .h générés
         */
        void saveFiles();

    protected:
        //Layouts
        QVBoxLayout *m_principalLayout;

        //Widgets
        QTextEdit *m_textCode;
        QTextEdit *m_textCpp;
        QPushButton *m_closeButton;
        QPushButton *m_saveButton;

        QTabWidget *m_tab;

        QWidget *m_pageCpp;
        QWidget *m_pageH;

        //Others
        QString m_codeClass;
        QString m_codeCpp;
        QString m_nameClass;

};

#endif // RESULTWINDOW_H
