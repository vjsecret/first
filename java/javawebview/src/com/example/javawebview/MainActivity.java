package com.example.javawebview;

import android.annotation.SuppressLint;
import android.app.Activity;
//import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Window;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

@SuppressLint("SetJavaScriptEnabled")
public class MainActivity extends Activity {
	private WebView mWebView = null;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
        
		//setContentView(R.layout.activity_main);

		getWindow().requestFeature(Window.FEATURE_NO_TITLE);
		mWebView = new WebView(this);
		WebSettings webSettings = mWebView.getSettings();
		webSettings.setJavaScriptEnabled(true);
		System.out.println("Hello Android");

		@Override
		public class WebView_404 extends Activity {	
			private Handler handler = new Handler() {
		    public void handleMessage(Message msg) {
		      if(msg.what==404) {//�D�����s�b
		        //���J���a assets ��Ƨ��U�������~���ܭ��� 404.html
		    	  System.out.println("error");
		      }
		    }
			};

		new Thread(new Runnable() {
	    public void run() {
			  Message msg = new Message();
			  //���B�P�_�D���O�_�s�b,�]���D���O�q�L loadUrl ���J��,
			  //���ɤ��|���� shouldOverrideUrlLoading �i�歶���O�_�s�b���P�_ //�i�J�D����,�I�D���̭����s��,�s�����L�����N�@�w�|����shouldOverrideUrlLoading ��k�F 
			  if(getRespStatus(HOMEPAGE)==404) {
		      msg.what = 404;
			  }
			  handler.sendMessage(msg);
		  }).start();

/*
        String myURL = "http://www.google.com.tw";
        WebView myBrowser=(WebView)findViewById(R.id.mybrowser);

        WebSettings websettings = myBrowser.getSettings();
        websettings.setSupportZoom(true);
        websettings.setBuiltInZoomControls(true); 
        websettings.setJavaScriptEnabled(true);
       
        myBrowser.setWebViewClient(new WebViewClient());

        myBrowser.loadUrl(myURL);*/
		 //WebViewClient mWebViewClient = new WebViewClient() {
		 mWebView.setWebViewClient(new WebViewClient() {
	      @Override
		  public boolean shouldOverrideUrlLoading(WebView view, String url) {
			    if(url.startsWith("http://") && getRespStatus(url)==404) {
				      view.stopLoading();
				      //���J���a assets ��Ƨ��U�������~���ܭ��� 404.html 
				      System.out.println("error");
				    }else{
				      view.loadUrl(url);
				    }
				      return true;
			  }
			 });
	         //};
        //mWebView.setWebViewClient(mWebViewClient);
	    this.setContentView(mWebView);
        mWebView.loadUrl("http://www.google.com.tw");
	}
/*
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	*/
}
