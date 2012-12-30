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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class MainWindow : public QWidget {
    Q_OBJECT

    public:
        MainWindow();

        /**
         * @brief initialise la fenêtre
         */
        void initWindow();

    public slots:
        /**
         * @brief generateClass => permet de générer une classe à partir des options
         */
        void generateClass();

        /**
         * @brief setTextHeader => slot permettant de récupérer le texte actuel d'un QLineEdit
         * @param t => référence sur le texte actuel
         */
        void setTextHeader(QString const& t);

        /**
         * @brief setTextHeaderEnabled => active/désactive le champ du header en fonction des cases à cocher
         * @param state
         */
        void setTextHeaderEnabled(int state);

        /**
         * @brief addProperty => ajoute un attribut dans le QListWidget
         */
        void addProperty();

        /**
         * @brief deleteProperty => supprime un item d'un QListWidget
         * @param item => l'item actuel
         */
        void deleteProperty(QListWidgetItem *item);

        /**
         * @brief addFile => ajoute un fichier dans le QListWidget
         */
        void addFile();

        /**
         * @brief deleteFile => supprime un fichier du QListWidget
         * @param item => l'item actuel
         */
        void deleteFile(QListWidgetItem *item);

    protected:
        //Layouts
        QVBoxLayout *m_principalLayout;
        QFormLayout *m_defineLayout;
        QVBoxLayout *m_optionsLayout;
        QVBoxLayout *m_propertiesLayout;
        QVBoxLayout *m_includeLayout;
        QFormLayout *m_commentariesLayout;
        QHBoxLayout *m_buttonsLayout;

        //Groups
        QGroupBox *m_defineGroup;
        QGroupBox *m_optionsGroup;
        QGroupBox *m_propertiesGroup;
        QGroupBox *m_includeGroup;
        QGroupBox *m_commentariesGroup;

        //Widgets
        QLineEdit *m_nameClassEdit;
        QLineEdit *m_parentClassEdit;

        QCheckBox *m_protection;
        QLineEdit *m_headerEdit;
        QCheckBox *m_constructor;
        QCheckBox *m_destructor;
        QCheckBox *m_license;

        QListWidget *m_properties;
        QPushButton *m_addPropButton;
        QLabel *m_label;

        QListWidget *m_includes;
        QPushButton *m_addIncludeButton;
        QLabel *m_labelInclude;

        QLineEdit *m_authorClass;
        QDateEdit *m_dateClass;
        QTextEdit *m_commentariesClass;

        QPushButton *m_generateButton;
        QPushButton *m_quitButton;

};

#endif // MAINWINDOW_H
