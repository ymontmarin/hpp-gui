#ifndef HPP_GUI_PATHPLAYER_HH
#define HPP_GUI_PATHPLAYER_HH

#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

#include <gepetto/gui/fwd.hh>

#include <hppwidgetsplugin/hppwidgetsplugin.hh>

namespace Ui {
  class PathPlayerWidget;
}

namespace hpp {
  namespace gui {
    class PathPlayer : public QWidget
    {
      Q_OBJECT

      public:
        PathPlayer (HppWidgetsPlugin* plugin, QWidget* parent = 0);
        ~PathPlayer();

        /// Returns the path currently selected.
        int getCurrentPath() const;

        public slots:
        /// Display the waypoints of a joint in the viewer.
        /// The waypoints are those of the currently selected path index.
        /// \param jointName name of the joint
          void displayWaypointsOfPath (const std::string jointName);

        /// Prepare the display of the path of a joint in the viewer.
        /// The path is took from the currently selected path index.
        /// \param jointName name of the joint
        void displayPath (const std::string jointName);

        /// Get the number of paths in hpp and refresh the gui accordingly.
        void update ();

      protected:
        /// Display the path of the jointName in the viewer.
        /// The path is took from the currently selected path index.
        /// \param jointName name of the joint
        virtual void displayPath_impl (const std::string jointName);
signals:
        void displayPath_status (int progress);

        private slots:
          void pathIndexChanged (int i);
        void pathSliderChanged (int value);
        //  void timeChanged (double d);
        void playPauseToggled (bool toggled);
        void stopClicked ();
        void recordToggled (bool toggled);
        void pathPulse ();
        void timerEvent(QTimerEvent *event);
        void readyReadProcessOutput ();

      private:
        void updateConfiguration ();
        double sliderToLength (int v) const;
        int lengthToSlider (double l) const;
        double timeToLength (double time) const;
        int timeBetweenRefresh() const;
        double lengthBetweenRefresh () const;

        ::Ui::PathPlayerWidget* ui_;

        QDoubleSpinBox* timeSpinBox () const;
        QSpinBox* pathIndex() const;
        QSlider* pathSlider () const;
        QPushButton* playPause () const;
        QPushButton* stop () const;
        QPushButton* record () const;

        double pathLength_;
        double currentParam_;
        int timerId_;

        QProcess* process_;
        QDialog* showPOutput_;
        QTextBrowser* pOutput_;

        HppWidgetsPlugin* plugin_;
    };
  } // namespace gui
} // namespace hpp

#endif // HPP_GUI_PATHPLAYER_HH
