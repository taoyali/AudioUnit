@file:OptIn(ExperimentalMaterial3Api::class, ExperimentalMaterial3Api::class)

package com.tyl.audiounit.ui

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.RowScope
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material.*
import androidx.compose.material.ContentAlpha
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.ProvideTextStyle
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.CompositionLocalProvider
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.constraintlayout.compose.ConstraintLayout
import androidx.constraintlayout.compose.ConstraintSet
import androidx.constraintlayout.compose.layoutId

/**
 * TopBar
 * @param title 标题
 * @param icon 图标
 */
@Composable
@Preview
fun AppToolBar(
    title: String = "Title",
    icon: ImageVector? = Icons.Filled.ArrowBack,
    backAction: () -> Unit = {},
    loginCompose: @Composable RowScope.() -> Unit = {},
) {
    TopAppBar(
        modifier = Modifier.fillMaxSize(),
        title = { Text(text = title) },
        navigationIcon = {
            icon?.let {
                IconButton(onClick = backAction) {
                    Icon(Icons.Filled.ArrowBack, "Back")
                }
            }
        },
        actions = loginCompose,
    )
}


@Composable
fun TopAppBarCenter(
    title: @Composable () -> Unit,
    modifier: Modifier = Modifier,
    navigationIcon: @Composable() (() -> Unit)? = null,
    backgroundColor: Color = MaterialTheme.colorScheme.primary,
    actions: @Composable() (RowScope.() -> Unit) = {},
    content: @Composable (PaddingValues) -> Unit
) {
    Scaffold(topBar = {
        val constraintSet = ConstraintSet {
            val titleRef = createRefFor("title")
            val navigationIconRef = createRefFor("navigationIcon")
            val actionsRef = createRefFor("actions")
            constrain(titleRef) {
                start.linkTo(parent.start)
                end.linkTo(parent.end)
                top.linkTo(parent.top)
                bottom.linkTo(parent.bottom)
            }
            constrain(navigationIconRef) {
                top.linkTo(parent.top)
                bottom.linkTo(parent.bottom)
            }
            constrain(actionsRef){
                top.linkTo(parent.top)
                bottom.linkTo(parent.bottom)
                end.linkTo(parent.end)
            }
        }
        val TopAppBarHeight = 56.dp
        ConstraintLayout(constraintSet,
            modifier = Modifier
                .fillMaxWidth()
                .background(backgroundColor)
                .height(TopAppBarHeight)
                .then(modifier)) {
            Box(
                Modifier
                    .layoutId("title")
                    .padding(horizontal = 4.dp)
            ) {
                ProvideTextStyle(value = MaterialTheme.typography.displayLarge) {
                    CompositionLocalProvider(
                        LocalContentAlpha provides ContentAlpha.high,
                        content = title
                    )
                }
            }
            if (navigationIcon != null) {
                Box(modifier = Modifier
                    .layoutId("navigationIcon")
                    .padding(start = 4.dp)) {
                    CompositionLocalProvider(
                        LocalContentAlpha provides ContentAlpha.high,
                        content = navigationIcon
                    )
                }
            }
            Row(
                Modifier.layoutId("actions").padding(end = 4.dp),
                content = actions
            )

        }
    }) {
        content(it)
    }
}
