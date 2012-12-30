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

#include "MainWindow.h"
#include "ResultWindow.h"

MainWindow::MainWindow() : QWidget() {
    //initialisation de la fenêtre
    initWindow();
    setWindowTitle("clGenerator - Générateur de classes C++");

    //Connexions
    connect(m_quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(m_generateButton, SIGNAL(clicked()), this, SLOT(generateClass()));
    connect(m_nameClassEdit, SIGNAL(textEdited(QString)), this, SLOT(setTextHeader(QString)));
    connect(m_protection, SIGNAL(stateChanged(int)), this, SLOT(setTextHeaderEnabled(int)));
    connect(m_addPropButton, SIGNAL(clicked()), this, SLOT(addProperty()));
    connect(m_properties, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(deleteProperty(QListWidgetItem*)));
    connect(m_addIncludeButton, SIGNAL(clicked()), this, SLOT(addFile()));
    connect(m_includes, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(deleteFile(QListWidgetItem*)));
}

void MainWindow::initWindow() {
    /**
     * @ - Définition de la classe
     **/
    m_nameClassEdit = new QLineEdit;
    QRegExp pattern("[A-Za-z0-9]{1,}");
    m_nameClassEdit->setValidator(new QRegExpValidator(pattern));

    m_parentClassEdit = new QLineEdit;

    m_defineLayout = new QFormLayout;
    m_defineLayout->addRow("&Nom", m_nameClassEdit);
    m_defineLayout->addRow("Classe &mère", m_parentClassEdit);

    m_defineGroup = new QGroupBox("Définition de la classe");
    m_defineGroup->setLayout(m_defineLayout);

    /**
     * @ - Options
     **/
    m_protection = new QCheckBox("Protéger le &header contre les inclusions multiples");
    m_protection->setChecked(true);
    m_headerEdit = new QLineEdit;

    QHBoxLayout *protectionLayout = new QHBoxLayout;
    protectionLayout->addWidget(m_protection);
    protectionLayout->addWidget(m_headerEdit);

    m_constructor = new QCheckBox("Générer un &constructeur par défaut");
    m_constructor->setChecked(true);
    m_destructor = new QCheckBox("Générer un &destructeur");
    m_license = new QCheckBox("Inclure le texte de la license GNU");

    m_optionsLayout = new QVBoxLayout;
    m_optionsLayout->addLayout(protectionLayout);
    m_optionsLayout->addWidget(m_constructor);
    m_optionsLayout->addWidget(m_destructor);
    m_optionsLayout->addWidget(m_license);

    m_optionsGroup = new QGroupBox("Options");
    m_optionsGroup->setLayout(m_optionsLayout);

    /**
     * @ - Attributs
     **/
    m_properties = new QListWidget;
    m_addPropButton = new QPushButton("Ajouter un attribut");
    m_label = new QLabel("(Double cliquez sur un attribut pour le supprimer)");

    m_propertiesLayout = new QVBoxLayout;
    m_propertiesLayout->addWidget(m_addPropButton);
    m_propertiesLayout->addWidget(m_label);
    m_propertiesLayout->addWidget(m_properties);

    m_propertiesGroup = new QGroupBox("Ajouter des attributs");
    m_propertiesGroup->setCheckable(true);
    m_propertiesGroup->setChecked(false);
    m_propertiesGroup->setLayout(m_propertiesLayout);

    /**
     * @ - Includes
     **/
    m_includes = new QListWidget;
    m_addIncludeButton = new QPushButton("Ajouter un fichier");
    m_labelInclude = new QLabel("(Double cliquez sur un fichier pour le supprimer)");

    m_includeLayout = new QVBoxLayout;
    m_includeLayout->addWidget(m_addIncludeButton);
    m_includeLayout->addWidget(m_labelInclude);
    m_includeLayout->addWidget(m_includes);

    m_includeGroup = new QGroupBox("Ajouter des fichiers à inclure");
    m_includeGroup->setCheckable(true);
    m_includeGroup->setChecked(false);
    m_includeGroup->setLayout(m_includeLayout);

    /**
     * @ - Commentaires
     **/
    m_authorClass = new QLineEdit;
    m_dateClass = new QDateEdit(QDate::currentDate());
    m_commentariesClass = new QTextEdit;

    m_commentariesLayout = new QFormLayout;
    m_commentariesLayout->addRow("&Auteur", m_authorClass);
    m_commentariesLayout->addRow("Da&te de création", m_dateClass);
    m_commentariesLayout->addRow("&Rôle de la classe", m_commentariesClass);

    m_commentariesGroup = new QGroupBox("Ajouter des commentaires");
    m_commentariesGroup->setCheckable(true);
    m_commentariesGroup->setChecked(true);
    m_commentariesGroup->setLayout(m_commentariesLayout);

    /**
     * @ - Boutons
     **/
    m_generateButton = new QPushButton("Générer");
    m_quitButton = new QPushButton("Quitter");

    m_buttonsLayout = new QHBoxLayout;
    m_buttonsLayout->addWidget(m_generateButton);
    m_buttonsLayout->addWidget(m_quitButton);
    m_buttonsLayout->setAlignment(Qt::AlignRight);


    /**
     * @ - Général
     **/
    m_principalLayout = new QVBoxLayout;
    m_principalLayout->addWidget(m_defineGroup);
    m_principalLayout->addWidget(m_optionsGroup);
    m_principalLayout->addWidget(m_propertiesGroup);
    m_principalLayout->addWidget(m_includeGroup);
    m_principalLayout->addWidget(m_commentariesGroup);
    m_principalLayout->addLayout(m_buttonsLayout);

    setLayout(m_principalLayout);
}

/**
 * SLOTS / SIGNALS
 **/

void MainWindow::generateClass() {
    QString codeClass;
    QString codeCpp;

    //on vérifie si le nom est bien rempli
    if(!m_nameClassEdit->text().isEmpty()) {
        /**
         * 1 - Récupération des commentaires
         **/
        if(m_license->isChecked()) {
            codeClass += "/*\n";
            codeClass += "This program is free software: you can redistribute it and/or modify";
            codeClass += "it under the terms of the GNU General Public License as published by";
            codeClass += "the Free Software Foundation, either version 3 of the License, or" ;
            codeClass += "(at your option) any later version.\n\n" ;

            codeClass += "This program is distributed in the hope that it will be useful,";
            codeClass += "but WITHOUT ANY WARRANTY; without even the implied warranty of";
            codeClass += "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the";
            codeClass += "GNU General Public License for more details.\n\n";

            codeClass += "You should have received a copy of the GNU General Public License";
            codeClass += "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n";
            codeClass += "*/\n\n";

            codeCpp += "/*\n";
            codeCpp += "This program is free software: you can redistribute it and/or modify";
            codeCpp += "it under the terms of the GNU General Public License as published by";
            codeCpp += "the Free Software Foundation, either version 3 of the License, or" ;
            codeCpp += "(at your option) any later version.\n\n" ;

            codeCpp += "This program is distributed in the hope that it will be useful,";
            codeCpp += "but WITHOUT ANY WARRANTY; without even the implied warranty of";
            codeCpp += "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the";
            codeCpp += "GNU General Public License for more details.\n\n";

            codeCpp += "You should have received a copy of the GNU General Public License";
            codeCpp += "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n";
            codeCpp += "*/\n\n";
        }

        if(m_commentariesGroup->isChecked()) {
            codeClass += "/*\n";

            if(!m_authorClass->text().isEmpty()) {
                codeClass += "Auteur : " + m_authorClass->text() + "\n";
            }

            codeClass += "Date de création : " + m_dateClass->text();

            if(!m_commentariesClass->toPlainText().isEmpty()) {
                codeClass += "\n\nRôle :\n";
                codeClass += "" + m_commentariesClass->toPlainText();
            }

            codeClass += "\n*/\n\n";
        }

        /**
         * 2 - Vérification des options
         **/
        codeCpp += "#include \"" + m_nameClassEdit->text().left(1).toUpper() + m_nameClassEdit->text().mid(1) + ".h\"\n";

        //Protection du header
        if(m_protection->isChecked()) {
            codeClass += "#ifndef " + m_headerEdit->text().toUpper() + "\n";
            codeClass += "#define " + m_headerEdit->text().toUpper() + "\n\n";
        }

        //Include des fichiers
        if(m_includeGroup->isChecked()) {
            QString files;

            for(int i(0); i < m_includes->count(); i++) {
                files += "#include \"" + m_includes->item(i)->text() + "\"\n";
            }

            codeClass += files + "\n\n";
        }

        codeClass += "class " + m_nameClassEdit->text();

        //Héritage
        QString extendsCpp;
        if(!m_parentClassEdit->text().isEmpty()) {
            extendsCpp = " : " + m_parentClassEdit->text() + "()";
            codeClass += " : public " + m_parentClassEdit->text();
        }

        codeClass += "\n";
        codeClass += "{\n";
        codeClass += "  public:\n";

        //Génération du constructeur
        if(m_constructor->isChecked()) {
            codeClass += "      " + m_nameClassEdit->text() + "();\n";
            codeCpp += "\n" + m_nameClassEdit->text() + "::" + m_nameClassEdit->text() + "()" + extendsCpp + "\n";
            codeCpp += "{\n\n";
            codeCpp += "}\n\n";
        }

        //Destructeur
        if(m_destructor->isChecked()) {
            codeClass += "      ~" + m_nameClassEdit->text() + "();\n";
            codeCpp += m_nameClassEdit->text() + "::~" + m_nameClassEdit->text() + "() { \n\n\n}\n\n";
        }

        //Accesseurs
        if(m_propertiesGroup->isChecked()) {
            QString accesseurs;
            QString accesseursCpp;

            for(int i(0); i < m_properties->count(); i++) {
                QString nameProp(m_properties->item(i)->text());
                QStringList list = nameProp.split(" ");

                //on vérifie si l'attribut n'est pas un pointeur
                if(list.at(1)[0] != '*' && list.at(1)[1] != '_') {
                    accesseurs += "      " + list.at(0) + " get" + list.at(1).left(1).toUpper() + list.at(1).mid(1) + "();\n";
                    accesseurs += "      void set" + list.at(1).left(1).toUpper() + list.at(1).mid(1) + "(" + list.at(0) + " " + list.at(1) + ");\n\n";

                    //Getters
                    accesseursCpp += list.at(0) + " " + m_nameClassEdit->text() + "::get" + list.at(1).left(1).toUpper() + list.at(1).mid(1) + "()\n";
                    accesseursCpp += "{\n";
                    accesseursCpp += "  return " + list.at(1) + ";\n";
                    accesseursCpp += "}\n\n";

                    //Setter
                    accesseursCpp += "void " + m_nameClassEdit->text() + "::set" + list.at(1).left(1).toUpper() + list.at(1).mid(1) + "(" + list.at(0) + " v_" + list.at(1) + ")\n";
                    accesseursCpp += "{\n";
                    accesseursCpp += "  "  + list.at(1) + " = v_" + list.at(1) + "; \n";
                    accesseursCpp += "}\n\n";
                }
            }

            codeClass += accesseurs;
            codeCpp += accesseursCpp;
        }

        codeClass += "\n\n\n";

        codeClass += "  protected:\n";

        //Génération des attributs
        if(m_propertiesGroup->isChecked()) {
            QString attributs;

            for(int i(0); i < m_properties->count(); i++) {
                attributs += "      " + m_properties->item(i)->text() + ";\n";
            }

            codeClass += attributs;
        }

        codeClass += "\n\n\n";

        codeClass += "  private:\n";
        codeClass += "\n\n\n";

        codeClass += "};\n";

        codeClass += "\n";

        if(m_protection->isChecked()) {
            codeClass += "#endif";
        }

        /**
         * 3 - Ouverture de la fenêtre de résultat
         **/
        QString nameClass(m_nameClassEdit->text());
        ResultWindow *result = new ResultWindow(codeClass, codeCpp, nameClass, this);
        result->exec();
    } else {
        QMessageBox::critical(this, "Erreur", "Le champ \"Nom\" doit être rempli.");
    }
}

void MainWindow::setTextHeader(QString const& t) {
    if(m_protection->isChecked()) {
        if(!m_nameClassEdit->text().isEmpty()) {
            m_headerEdit->setText("HEADER_" + t.toUpper());
        } else {
            m_headerEdit->clear();
        }
    }
}

void MainWindow::setTextHeaderEnabled(int state) {
    if(state == Qt::Checked) {
        m_headerEdit->setEnabled(true);
        setTextHeader(m_nameClassEdit->text());
    } else {
        m_headerEdit->setEnabled(false);
        m_headerEdit->clear();
    }
}

void MainWindow::addProperty() {
    bool ok = false;
    QString property = QInputDialog::getText(this, "Saisir une information", "Entrez votre attribut (avec le type)", QLineEdit::Normal, QString(), &ok);

    if(ok && !property.isEmpty()) {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(property);
        m_properties->insertItem(m_properties->currentRow() + 1, newItem);
    }
}

void MainWindow::deleteProperty(QListWidgetItem *item) {
    m_properties->takeItem(m_properties->currentRow());
    item = 0;
}

void MainWindow::addFile() {
    bool ok = false;
    QString fileName = QInputDialog::getText(this, "Saisir une information", "Entrez le nom de votre fichier", QLineEdit::Normal, QString(), &ok);

    if(ok && !fileName.isEmpty()) {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(fileName);
        m_includes->insertItem(m_includes->currentRow() + 1, newItem);
    }
}

void MainWindow::deleteFile(QListWidgetItem *item) {
    m_includes->takeItem(m_includes->currentRow());
    item = 0;
}
