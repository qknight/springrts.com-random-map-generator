/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Document.h"
#include "Model.h"
#include "GraphicsScene.h"
#include "ItemView.h"

Document::Document() {
    model = new Model;
    
    // filter elements out for the QTreeView
    filter = new FilterProxyModel;
    filter->setSourceModel(model);
    
    scene = new GraphicsScene(model);
    itemView = new ItemView(scene, model);

    scene->setLoadableModuleNames(model->LoadableModuleNames());
    connect(scene, SIGNAL(CreateModuleSignal(QString,QPoint)),
            this, SLOT(CreateModuleSlot(QString,QPoint)));

    // WARNING: this interface using the model with insertModule is only a hack and will not be used
    //          - it is there to make testing easier
    //          - after the xml save/load function is implemented
    //          - additionally: this interface is not guaranteed to be stable
    QModelIndex m1 = model->insertModule("Generator::Billow",   QPoint(-200,-100));
    QModelIndex m2 = model->insertModule("Generator::Perlin",   QPoint(-200,100));
    QModelIndex m3 = model->insertModule("Generator::Perlin",   QPoint( 0,250));
    QModelIndex m4 = model->insertModule("Selector::Select", QPoint(100,0));
    QModelIndex m5 = model->insertModule("Utils::Image" ,   QPoint( 350,50));
    QModelIndex m6 = model->insertModule("Spring::Mapgenerator" ,   QPoint( 300,250));

//     QModelIndex m1_output1 = m1.child(model->rowCount(m1)-1,0);
//     QModelIndex m2_output1 = m2.child(model->rowCount(m2)-1,0);
//     QModelIndex m3_output1 = m3.child(model->rowCount(m3)-1,0);
// 
//     QModelIndex m4_input1 = m4.child(0,0);
//     QModelIndex m4_input2 = m4.child(1,0);
//     QModelIndex m4_modput1 = m4.child(2,0);
//     QModelIndex m4_output1 = m4.child(3,0);
// 
//     QModelIndex m5_input1 = m5.child(model->rowCount(m5)-1,0);
// 
//     model->insertConnection(m1_output1, m4_input1);
//     model->insertConnection(m2_output1, m4_input2);
//     model->insertConnection(m3_output1, m4_modput1);
//     model->insertConnection(m4_output1, m5_input1);

    scene->addLine(-100,0,100,0);
    scene->addLine(0,-100,0,100);
}

Document::~Document() {
    delete itemView;
    delete scene;
    delete filter;
    delete model;
}

void Document::CreateModuleSlot(QString type, QPoint position) {
    model->insertModule(type, position);
}
