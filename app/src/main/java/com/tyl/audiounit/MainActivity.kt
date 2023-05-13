package com.tyl.audiounit

import android.app.Activity
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.tyl.audiounit.ui.TopAppBarCenter
import com.tyl.opensl.AudioOpenSLJava
import com.tyl.opensl.AudioOpenSLKotlin


class MainActivity : ComponentActivity() {

    private val dataList = listOf(
        ActionModel("Audio - OpenSL ES", action = {

            println("OpenSL ES action start")
            // native test
            val result = AudioOpenSLKotlin.printLog("hello native")
            println("OpenSL ES result = " + result)
            println("OpenSL ES action end")
        }),
        ActionModel("Audio - Oboe", action = {

            println("Oboe action start")
            // native test
            val result = AudioOpenSLJava.printLog("hello native")
            println("Oboe result = " + result)
            println("Oboe action end")
        }),
//        ActionModel("Audio - ", action = {
//
//        }),
//        ActionModel("Audio - ", action = {
//
//        }),
    )

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContent {
            val context = LocalContext.current as Activity
            MaterialTheme {
                TopAppBarCenter(
                    title = {
                        Text(text = "Media", color = Color.White, fontSize = 16.sp)
                    },
                    Modifier
                ) {
                    Spacer(modifier = Modifier.height(100.dp))
//                    Greeting("Android", Modifier.fillMaxHeight(), dataList)
                    MidiaColumn(dataList)
                }
            }
        }
    }
}

data class ActionModel(val title: String, val action: () -> Unit)

@Composable
fun MidiaColumn(list: List<ActionModel>) {
    val titleTextStyle = TextStyle(fontWeight = FontWeight.Black, fontSize = 14.sp)
    Column {
        Spacer(modifier = Modifier.height(50.dp))
        Box(
            modifier = Modifier.fillMaxSize(),
            contentAlignment = Alignment.Center)
        {
            LazyColumn(
                modifier = Modifier.fillMaxWidth(),
                verticalArrangement = Arrangement.Top,
                horizontalAlignment = Alignment.CenterHorizontally
            ) {
                items(list.count()) {
                    Button(onClick = {
                        println("tap action")
                        list[it].action()
                    }, colors = ButtonDefaults.buttonColors()) {
                        Text(text = list[it].title, style = titleTextStyle)
                    }
                }
            }
        }
    }
}