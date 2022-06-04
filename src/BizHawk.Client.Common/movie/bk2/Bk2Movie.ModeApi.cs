using System;
using System.Linq;

namespace BizHawk.Client.Common
{
	public partial class Bk2Movie
	{
		private MovieMode _mode = MovieMode.Inactive;

		public MovieMode Mode
		{
			get => _mode;
			protected set
			{
				OnModeChange?.Invoke(_mode, value);
				_mode = value;
			}
		}

		public event Action<MovieMode, MovieMode> OnModeChange;

		public virtual void StartNewRecording()
		{
			Mode = MovieMode.Record;
			if (Session.Settings.EnableBackupMovies && MakeBackup && Log.Any())
			{
				SaveBackup();
				MakeBackup = false;
			}

			Log.Clear();
		}

		public void StartNewPlayback() => Mode = MovieMode.Play;
		public void SwitchToRecord() => Mode = MovieMode.Record;
		public void SwitchToPlay() => Mode = MovieMode.Play;
		public void FinishedMode() => Mode = MovieMode.Finished;

		public virtual bool Stop(bool saveChanges = true)
		{
			bool saved = false;
			if (saveChanges)
			{
				if (Mode == MovieMode.Record || (this.IsActive() && Changes))
				{
					Save();
					saved = true;
				}
			}

			Changes = false;
			Mode = MovieMode.Inactive;

			return saved;
		}
	}
}
