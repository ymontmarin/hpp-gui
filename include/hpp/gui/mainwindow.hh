#ifndef HPP_GUI_MAINWINDOW_HH
#define HPP_GUI_MAINWINDOW_HH

#include <QList>
#include <QStandardItemModel>
#include <QMainWindow>

#include <gepetto/viewer/group-node.h>

#include <hpp/gui/fwd.hh>

#include <hpp/gui/ledindicator.hh>

#include <hpp/gui/omniorb/omniorbthread.hh>
#include <hpp/gui/dialog/dialogloadrobot.hh>
#include <hpp/gui/dialog/dialogloadenvironment.hh>
#include <hpp/gui/dialog/pluginmanagerdialog.hh>

#include <hpp/gui/settings.hh>

namespace Ui {
  class MainWindow;
}

namespace hpp {
  namespace gui {
    class MainWindow : public QMainWindow
    {
      Q_OBJECT

      public:
        explicit MainWindow(Settings settings, QWidget *parent = 0);
        ~MainWindow();

        static MainWindow* instance ();

        void insertDockWidget (QDockWidget* dock,
            Qt::DockWidgetArea area = Qt::AllDockWidgetAreas,
            Qt::Orientation orientation = Qt::Horizontal);

        void removeDockWidget (QDockWidget* dock);

        BackgroundQueue &worker();

        WindowsManagerPtr_t osg () const;

        OSGWidget* centralWidget() const;

        PluginManager* pluginManager ();

      public:
        QItemSelectionModel* bodySelectionModel ();
signals:
        void selectedBodyChanged (const QStringList& selected, const QStringList& deselected);
        public slots:
          void selectBodyByName (const QString& bodyName);
        private slots:
          void bodySelectionChanged (const QItemSelection & selected, const QItemSelection & deselected);

      public:
        void log (const QString& text);
        void logError (const QString& text);

        void emitSendToBackground (WorkItem* item);

signals:
        void sendToBackground (WorkItem* item);
        void createView (QString name);
        void refresh ();
        void applyCurrentConfiguration();
        void configurationValidation();
        void selectJointFromBodyName(const std::string &bodyName);

        public slots:
          void logJobStarted (int id, const QString& text);
        void logJobDone    (int id, const QString& text);
        void logJobFailed  (int id, const QString& text);

        OSGWidget* delayedCreateView (QString name = "");
        void requestRefresh ();
        void reloadBodyTree ();
        void addBodyToTree (graphics::GroupNodePtr_t group);
        void requestApplyCurrentConfiguration ();
        void requestConfigurationValidation ();
        void configurationValidationStatusChanged (bool valid);
        void configurationValidationStatusChanged (QStringList bodiesInCollision);
        void requestSelectJointFromBodyName (const std::string& bodyName);
        void onOpenPluginManager ();

        private slots:
          OSGWidget* onCreateView();
        void openLoadRobotDialog ();
        void openLoadEnvironmentDialog ();
        void updateBodyTree (const QModelIndex& index);
        void showTreeContextMenu (const QPoint& point);

        void handleWorkerDone (int id);

        void resetConnection ();
        void about ();

      private:
        void setupInterface ();
        void createCentralWidget ();
        void readSettings ();
        void writeSettings ();

        static MainWindow* instance_;
        Settings settings_;

        ::Ui::MainWindow* ui_;
        OSGWidget* centralWidget_;
        QList <OSGWidget*> osgWindows_;

        WindowsManagerPtr_t osgViewerManagers_;
        CorbaServer osgServer_;
        BackgroundQueue backgroundQueue_;
        QThread worker_;

        QCheckBox* collisionValidationActivated_;
        LedIndicator* collisionIndicator_;

        QStandardItemModel *bodyTreeModel_;

        PluginManager pluginManager_;

        QMutex delayedCreateView_;
        QStringList robotNames_;
        QStringList lastBodiesInCollision_;
    };
  } // namespace gui
} // namespace hpp

#endif // HPP_GUI_MAINWINDOW_HH