const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');

// Main process config
const mainConfig = {
    mode: 'development',
    entry: './src/main.ts',
    target: 'electron-main',
    output: {
        path: path.resolve(__dirname, 'dist'),
        filename: 'main.js',
    },
    resolve: {
        extensions: ['.ts', '.js'],
    },
    module: {
        rules: [
            {
                test: /\.ts$/,
                use: 'ts-loader',
                exclude: /node_modules/,
            },
        ],
    },
    plugins: [],
    devtool: 'source-map',
    node: {
        __dirname: false,
        __filename: false,
    },
};

// Preload script config
const preloadConfig = {
    mode: 'development',
    entry: './src/preload.ts',
    target: 'electron-preload',
    output: {
        path: path.resolve(__dirname, 'dist'),
        filename: 'preload.js',
    },
    resolve: {
        extensions: ['.ts', '.js'],
    },
    module: {
        rules: [
            {
                test: /\.ts$/,
                use: 'ts-loader',
                exclude: /node_modules/,
            },
        ],
    },
    devtool: 'source-map',
};

// Renderer process config
const rendererConfig = {
    mode: 'development',
    entry: './src/renderer.tsx',
    target: 'electron-renderer',
    output: {
        path: path.resolve(__dirname, 'dist'),
        filename: 'renderer.js',
    },
    resolve: {
        extensions: ['.ts', '.tsx', '.js', '.jsx'],
    },
    module: {
        rules: [
            {
                test: /\.(ts|tsx)$/,
                use: 'ts-loader',
                exclude: /node_modules/,
            },
            {
                test: /\.css$/,
                use: ['style-loader', 'css-loader'],
            },
        ],
    },
    plugins: [
        new HtmlWebpackPlugin({
            template: './public/index.html',
            filename: 'index.html',
        }),
    ],
    devtool: 'source-map',
};

module.exports = [mainConfig, preloadConfig, rendererConfig];