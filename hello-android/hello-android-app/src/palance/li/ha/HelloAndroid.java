package palance.li.ha;

import android.app.Activity;
import android.os.ServiceManager;
import android.os.Bundle;
import android.os.IHAService;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class HelloAndroid extends Activity implements OnClickListener {
	private final static String LOG_TAG = "palance.li.ha.FregActivity";

	private IHAService 	haService 	= null;
	private EditText 	valueText 	= null;
	private Button 		readButton 	= null;
	private Button 		writeButton	= null;
	private Button 		clearButton	= null;

	@Override
	public void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		haService = IHAService.Stub.asInterface(
			ServiceManager.getService("ha"));

		valueText = (EditText)findViewById(R.id.edit_value);
		readButton = (Button)findViewById(R.id.button_read);
		writeButton = (Button)findViewById(R.id.button_write);
		clearButton = (Button)findViewById(R.id.button_clear);

		readButton.setOnClickListener(this);
		writeButton.setOnClickListener(this);
		clearButton.setOnClickListener(this);

		Log.i(LOG_TAG, "Ha Activity Created.");
	}

	@Override
	public void onClick(View v){
		if(v.equals(readButton)){
			try{
				int value = haService.getValue();
				String text = String.valueOf(value);
				valueText.setText(text);
			}catch(RemoteException e){
				Log.e(LOG_TAG, "Remote Exception while reading value from ha service.");
			}
		}else if(v.equals(writeButton)){
			try{
				String text = valueText.getText().toString();
				int value = Integer.parseInt(text);
				haService.setValue(value);
			}catch(RemoteException e){
				Log.e(LOG_TAG, "Remote Exception while writing value to ha service.");
			}
		}else if(v.equals(clearButton)){
			String text = "";
			valueText.setText(text);
		}
	}
}